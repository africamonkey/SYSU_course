import numpy as np
import pandas as pd

from sklearn.feature_extraction.text import CountVectorizer
import itertools

import re
from keras.preprocessing.sequence import pad_sequences
from sklearn.model_selection import train_test_split

import keras.layers as lyr
from keras.models import Model

df_train = pd.read_csv('../input/train.csv', encoding='utf-8')
df_train['id'] = df_train['id'].apply(str)

df_test = pd.read_csv('../input/test.csv', encoding='utf-8')
df_test['test_id'] = df_test['test_id'].apply(str)

df_all = pd.concat((df_train, df_test))
df_all['question1'].fillna('', inplace=True)
df_all['question2'].fillna('', inplace=True)


counts_vectorizer = CountVectorizer(max_features=10000-1).fit(
    itertools.chain(df_all['question1'], df_all['question2']))
other_index = len(counts_vectorizer.vocabulary_)

words_tokenizer = re.compile(counts_vectorizer.token_pattern)


def create_padded_seqs(texts, max_len=10):
    seqs = texts.apply(lambda s:
        [counts_vectorizer.vocabulary_[w] if w in counts_vectorizer.vocabulary_ else other_index
         for w in words_tokenizer.findall(s.lower())])
    return pad_sequences(seqs, maxlen=max_len)


X1_train, X1_val, X2_train, X2_val, y_train, y_val = \
    train_test_split(create_padded_seqs(df_all[df_all['id'].notnull()]['question1']),
                     create_padded_seqs(df_all[df_all['id'].notnull()]['question2']),
                     df_all[df_all['id'].notnull()]['is_duplicate'].values,
                     stratify=df_all[df_all['id'].notnull()]['is_duplicate'].values,
                     test_size=0.1, random_state=4242)

input1_tensor = lyr.Input(X1_train.shape[1:])
input2_tensor = lyr.Input(X2_train.shape[1:])
words_embedding_layer = lyr.Embedding(X1_train.max() + 1, 100)
seq_embedding_layer = lyr.LSTM(64, activation='tanh')
seq_embedding = lambda tensor: seq_embedding_layer(words_embedding_layer(tensor))
merge_layer = lyr.multiply([seq_embedding(input1_tensor), seq_embedding(input2_tensor)])
dense1_layer = lyr.Dense(16, activation='sigmoid')(merge_layer)
ouput_layer = lyr.Dense(1, activation='sigmoid')(dense1_layer)
model = Model([input1_tensor, input2_tensor], ouput_layer)
model.compile(loss='binary_crossentropy', optimizer='adam')
model.summary()

model.fit([X1_train, X2_train], y_train,
          validation_data=([X1_val, X2_val], y_val),
          batch_size=128, epochs=6, verbose=2)

features_model = Model([input1_tensor, input2_tensor], merge_layer)
features_model.compile(loss='mse', optimizer='adam')

X1_train = create_padded_seqs(df_all[df_all['id'].notnull()]['question1'])
X2_train = create_padded_seqs(df_all[df_all['id'].notnull()]['question2'])
X1_test = create_padded_seqs(df_all[df_all['test_id'].notnull()]['question1'])
X2_test = create_padded_seqs(df_all[df_all['test_id'].notnull()]['question2'])

F_train = features_model.predict([X1_train, X2_train], batch_size=128)
F_test = features_model.predict([X1_test, X2_test], batch_size=128)

name = []
for i in range(0, 64):
    name.append('lstm' + str(i))
F_train_df = pd.DataFrame(F_train, columns=name)
F_train_df.index.name = 'id'
F_train_df.to_csv("../input/lstm_train.csv")

F_test_df = pd.DataFrame(F_test, columns=name)
F_test_df.index.name = 'test_id'
F_test_df.to_csv("../input/lstm_test.csv")
