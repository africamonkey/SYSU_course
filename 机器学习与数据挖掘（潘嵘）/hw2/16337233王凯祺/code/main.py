import numpy as np # linear algebra
import re
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
from sklearn.metrics import log_loss
import matplotlib.pyplot as plt
from nltk import word_tokenize, pos_tag
from nltk.corpus import wordnet
from nltk.stem import WordNetLemmatizer
from nltk.corpus import stopwords
from nltk.stem import SnowballStemmer
from string import punctuation
import nltk
from collections import Counter
from sklearn.model_selection import train_test_split
from gensim.models import word2vec
import Levenshtein
import xgboost as xgb


def word_match_share(row):
    global stops
    q1words = {}
    q2words = {}
    for word in str(row['question1']).lower().split():
        if word not in stops:
            q1words[word] = 1
    for word in str(row['question2']).lower().split():
        if word not in stops:
            q2words[word] = 1
    if len(q1words) == 0 or len(q2words) == 0:
        # The computer-generated chaff includes a few questions that are nothing but stopwords
        return 0
    shared_words_in_q1 = [w for w in q1words.keys() if w in q2words]
    shared_words_in_q2 = [w for w in q2words.keys() if w in q1words]
    R = (len(shared_words_in_q1) + len(shared_words_in_q2))/(len(q1words) + len(q2words))
    return R


def text_to_wordlist(text, remove_stop_words=True, stem_words=False):
    # Clean the text, with the option to remove stop_words and to stem words.
    global stops
    text = re.sub(r"[^A-Za-z0-9]", " ", text)
    text = re.sub(r"what's", "", text)
    text = re.sub(r"What's", "", text)
    text = re.sub(r"\'s", " ", text)
    text = re.sub(r"\'ve", " have ", text)
    text = re.sub(r"can't", "cannot ", text)
    text = re.sub(r"n't", " not ", text)
    text = re.sub(r"I'm", "I am", text)
    text = re.sub(r" m ", " am ", text)
    text = re.sub(r"\'re", " are ", text)
    text = re.sub(r"\'d", " would ", text)
    text = re.sub(r"\'ll", " will ", text)
    text = re.sub(r"60k", " 60000 ", text)
    text = re.sub(r" e g ", " eg ", text)
    text = re.sub(r" b g ", " bg ", text)
    text = re.sub(r"\0s", "0", text)
    text = re.sub(r" 9 11 ", "911", text)
    text = re.sub(r"e-mail", "email", text)
    text = re.sub(r"\s{2,}", " ", text)
    text = re.sub(r"quikly", "quickly", text)
    text = re.sub(r" usa ", " America ", text)
    text = re.sub(r" USA ", " America ", text)
    text = re.sub(r" u s ", " America ", text)
    text = re.sub(r" uk ", " England ", text)
    text = re.sub(r" UK ", " England ", text)
    text = re.sub(r"india", "India", text)
    text = re.sub(r"switzerland", "Switzerland", text)
    text = re.sub(r"china", "China", text)
    text = re.sub(r"chinese", "Chinese", text)
    text = re.sub(r"imrovement", "improvement", text)
    text = re.sub(r"intially", "initially", text)
    text = re.sub(r"quora", "Quora", text)
    text = re.sub(r" dms ", "direct messages ", text)
    text = re.sub(r"demonitization", "demonetization", text)
    text = re.sub(r"actived", "active", text)
    text = re.sub(r"kms", " kilometers ", text)
    text = re.sub(r"KMs", " kilometers ", text)
    text = re.sub(r" cs ", " computer science ", text)
    text = re.sub(r" upvotes ", " up votes ", text)
    text = re.sub(r" iPhone ", " phone ", text)
    text = re.sub(r"\0rs ", " rs ", text)
    text = re.sub(r"calender", "calendar", text)
    text = re.sub(r"ios", "operating system", text)
    text = re.sub(r"gps", "GPS", text)
    text = re.sub(r"gst", "GST", text)
    text = re.sub(r"programing", "programming", text)
    text = re.sub(r"bestfriend", "best friend", text)
    text = re.sub(r"dna", "DNA", text)
    text = re.sub(r"III", "3", text)
    text = re.sub(r"the US", "America", text)
    text = re.sub(r"Astrology", "astrology", text)
    text = re.sub(r"Method", "method", text)
    text = re.sub(r"Find", "find", text)
    text = re.sub(r"banglore", "Banglore", text)
    text = re.sub(r" J K ", " JK ", text)

    # Remove punctuation from text
    text = ''.join([c for c in text if c not in punctuation])

    # Optionally, remove stop words
    if remove_stop_words:
        text = text.split()
        text = [w for w in text if not w in stops]
        text = " ".join(text)

    # Optionally, shorten words to their stems
    if stem_words:
        text = text.split()
        stemmer = SnowballStemmer('english')
        stemmed_words = [stemmer.stem(word) for word in text]
        text = " ".join(stemmed_words)

    # Return a list of words
    return text


def clean_data_frame(row):
    row['question1'] = text_to_wordlist(str(row['question1']))
    row['question2'] = text_to_wordlist(str(row['question2']))
    return row


def get_weight(count, eps=10000, min_count=2):
    if count < min_count:
        return 0
    else:
        return 1 / (count + eps)


def tfidf_word_match_share(row):
    global stops, weights, counts, words
    q1words = {}
    q2words = {}
    for word in str(row['question1']).lower().split():
        if word not in stops:
            q1words[word] = 1
    for word in str(row['question2']).lower().split():
        if word not in stops:
            q2words[word] = 1
    if len(q1words) == 0 or len(q2words) == 0:
        # The computer-generated chaff includes a few questions that are nothing but stopwords
        return 0
    shared_weights = [weights.get(w, 0) for w in q1words.keys() if w in q2words] + [weights.get(w, 0) for w in q2words.keys() if w in q1words]
    total_weights = [weights.get(w, 0) for w in q1words] + [weights.get(w, 0) for w in q2words]
    R = np.sum(shared_weights) / np.sum(total_weights)
    return R


def word2vec_similarity_match(row):
    global stops, w2vmodel
    qcnt = 0
    scnt = 0
    for word1 in str(row['question1']).lower().split():
        if word1 not in stops:
            for word2 in str(row['question2']).lower().split():
                if word2 not in stops:
                    qcnt += 1
                    if word1 in w2vmodel and word2 in w2vmodel:
                        scnt += w2vmodel.wv.similarity(word1, word2)
    if qcnt == 0:
        return 0
    return scnt / qcnt


def word2vec_distance_match(row):
    global stops, w2vmodel
    qcnt = 0
    scnt = 0
    for word1 in str(row['question1']).lower().split():
        if word1 not in stops:
            for word2 in str(row['question2']).lower().split():
                if word2 not in stops:
                    qcnt += 1
                    if word1 in w2vmodel and word2 in w2vmodel:
                        scnt += w2vmodel.wv.distance(word1, word2)
                    else:
                        scnt += 1.0
    if qcnt == 0:
        return 1
    return scnt / qcnt


def edit_distance(row):
    ans = Levenshtein.distance(str(row['question1']), str(row['question2']))
    if ans > 150:
        ans = 150
    return ans


def edit_ratio(row):
    ans = Levenshtein.ratio(str(row['question1']), str(row['question2']))
    return ans


def pre_process_for_datas():
    df_train = pd.read_csv('../input/train.csv')
    print(df_train.head())

    df_train = df_train.apply(clean_data_frame, axis=1, raw=True)
    df_train.to_csv('../input/train_processed.csv', index=False)
    print(df_train.head())

    df_test = pd.read_csv('../input/test.csv')
    print(df_test.head())
    df_test = df_test.apply(clean_data_frame, axis=1, raw=True)
    df_test.to_csv('../input/test_processed.csv', index=False)
    print(df_test.head())


def build_corpus(data):
    corpus = []
    for col in ['question1', 'question2']:
        for sentence in data[col].iteritems():
            word_list = str(sentence[1]).lower().split(" ")
            corpus.append(word_list)
    return corpus


def print_plot(data, df_train, title, filename=None):
    plt.figure(figsize=(15, 5))
    plt.hist(data[df_train['is_duplicate'] == 0], bins=20, density=True, label='Not Duplicate')
    plt.hist(data[df_train['is_duplicate'] == 1], bins=20, density=True, alpha=0.7, label='Duplicate')
    plt.legend()
    plt.title(title, fontsize=15)
    plt.xlabel('word_match_share', fontsize=15)
    if filename is None or filename == '':
        plt.show()
    else:
        plt.savefig(filename)


if __name__ == '__main__':
    #    pre_process_for_datas()

    global stops, words, counts, weights, w2vmodel
    stops = set(stopwords.words("english"))
    df_train = pd.read_csv('../input/train_processed.csv')
    df_test = pd.read_csv('../input/test_processed.csv')

    corpus_train = build_corpus(df_train)
    corpus_test = build_corpus(df_test)
    corpus = corpus_train + corpus_test
    w2vmodel = word2vec.Word2Vec(corpus, size=100, window=20, min_count=500, workers=4)

    train_word_match = df_train.apply(word_match_share, axis=1, raw=True)
    print_plot(train_word_match, df_train, 'Label distribution over word_match_share', '1.png')

    train_qs = pd.Series(df_train['question1'].tolist() + df_train['question2'].tolist()).astype(str)
    test_qs = pd.Series(df_test['question1'].tolist() + df_test['question2'].tolist()).astype(str)
    words = (" ".join(train_qs)).lower().split()
    counts = Counter(words)
    weights = {word: get_weight(count) for word, count in counts.items()}
    tfidf_train_word_match = df_train.apply(tfidf_word_match_share, axis=1, raw=True)
    print_plot(tfidf_train_word_match, df_train, 'Label distribution over tfidf_word_match_share', '2.png')

    train_w2v_similarity_match = df_train.apply(word2vec_similarity_match, axis=1, raw=True)
    print_plot(train_w2v_similarity_match, df_train, 'Label distribution over w2v similarity match', '3.png')

    train_w2v_distance_match = df_train.apply(word2vec_distance_match, axis=1, raw=True)
    print_plot(train_w2v_distance_match, df_train, 'Label distribution over w2v distance match', '4.png')

    train_edit_distance = df_train.apply(edit_distance, axis=1, raw=True)
    print_plot(train_edit_distance, df_train, 'Label distribution over edit distance', '5.png')

    train_edit_ratio = df_train.apply(edit_ratio, axis=1, raw=True)
    print_plot(train_edit_ratio, df_train, 'Label distribution over edit ratio', '6.png')

    x_train_lstm = pd.read_csv('../input/lstm_train.csv')
    x_test_lstm = pd.read_csv('../input/lstm_test.csv')

    del x_train_lstm['id']
    del x_test_lstm['test_id']

    x_train = pd.DataFrame()
    x_test = pd.DataFrame()
    x_train['word_match'] = train_word_match
    x_train['tfidf_word_match'] = tfidf_train_word_match
    x_train['w2v_similarity_match'] = train_w2v_similarity_match
    x_train['w2v_distance_match'] = train_w2v_distance_match
    x_train['edit_distance'] = train_edit_distance
    x_train['edit_ratio'] = train_edit_ratio
    x_test['word_match'] = df_test.apply(word_match_share, axis=1, raw=True)
    x_test['tfidf_word_match'] = df_test.apply(tfidf_word_match_share, axis=1, raw=True)
    x_test['w2v_similarity_match'] = df_test.apply(word2vec_similarity_match, axis=1, raw=True)
    x_test['w2v_distance_match'] = df_test.apply(word2vec_distance_match, axis=1, raw=True)
    x_test['edit_distance'] = df_test.apply(edit_distance, axis=1, raw=True)
    x_test['edit_ratio'] = df_test.apply(edit_ratio, axis=1, raw=True)
    y_train = df_train['is_duplicate'].values

    x_train = pd.merge(x_train, x_train_lstm, how='inner', left_index=True, right_index=True)
    x_test = pd.merge(x_test, x_test_lstm, how='inner', left_index=True, right_index=True)

    pos_train = x_train[y_train == 1]
    neg_train = x_train[y_train == 0]

    # Now we oversample the negative class
    # There is likely a much more elegant way to do this...
    len_ori_neg_train = len(neg_train)
    p = 0.1293
    scale = ((len(pos_train) / (len(pos_train) + len(neg_train))) / p) - 1
    while scale > 1:
        neg_train = pd.concat([neg_train, neg_train[:len_ori_neg_train]])
        scale -= 1
    neg_train = pd.concat([neg_train, neg_train[:int(scale * len_ori_neg_train)]])
    print(len(pos_train) / (len(pos_train) + len(neg_train)))

    x_train = pd.concat([pos_train, neg_train])
    y_train = (np.zeros(len(pos_train)) + 1).tolist() + np.zeros(len(neg_train)).tolist()
    del pos_train, neg_train
    x_train, x_valid, y_train, y_valid = train_test_split(x_train, y_train, test_size=0.1, random_state=4242)

    # Set our parameters for xgboost
    params = {}
    params['objective'] = 'binary:logistic'
    params['eval_metric'] = 'logloss'
    params['eta'] = 0.015
    params['max_depth'] = 4

    d_train = xgb.DMatrix(x_train, label=y_train)
    d_valid = xgb.DMatrix(x_valid, label=y_valid)

    watchlist = [(d_train, 'train'), (d_valid, 'valid')]
    bst = xgb.train(params, d_train, 10, watchlist, early_stopping_rounds=50, verbose_eval=10)

    for i in range(2, 1000):
        iters = i * 10
        print('training ' + str(iters) + ':')
        bst_2 = xgb.train(params, d_train, 10, watchlist, early_stopping_rounds=50, verbose_eval=10, xgb_model=bst)
        bst = bst_2

        d_test = xgb.DMatrix(x_test)
        p_test = bst.predict(d_test)

        sub = pd.DataFrame()
        sub['test_id'] = df_test['test_id']
        sub['is_duplicate'] = p_test
        sub.to_csv('simple_xgb_6_iter' + str(iters) + '_lstm.csv', index=False)
