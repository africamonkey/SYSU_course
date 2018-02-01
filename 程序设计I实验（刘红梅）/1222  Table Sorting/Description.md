# Table Sorting

# Description

This time I beg that you pay efforts to read the description carefully. I just couldn't imagine how one would attempt to figure out what the assignment is asking him to do without reading the description when on some occasions one still has no idea what the f** it is about even after reading.

Some students complain that TAs are so inhumane as to deprive students of the freedom to write their own ``main.c`` without realizing the fact that those assignments are aimed at the practice of the usage of the language features as well as grammar, but not merely at solving the problem arising in the assignment (solving the problem as we want would be easy, but that's how a person works, not how a team works). However, with several weeks' such practice I kind of believe that (OK, I still doubt about it) now you have a good master of this language filled with frustrating ``types``, ``pointers`` and ``structures``. Maybe it is time you write your own ``main.c``, or we would consider freezing ``main.c`` again if no more than 90% of you guys got full scores in this assignment.

Well I regret to say that we have to do the sorting stuff again. Today (maybe several days for you) we sort a table by one of its columns.

First we read a table, then we sort the table by some specified column and print the result. The point is that when a cell of the specified column gets swapped, those on the same row (or ``record``) as that cell move parallel and get swapped too.

Take the following table as an example

```
Gender Name   Id       Score
f      Asuna  16383424 100  
m      Kurain 16349834 59   
m      Kirito 16354323 98   
f      Sirika 16325352 60   

```

When the table is sorted by Name, in the result the names should be sorted, and more importantly, Gender, Id and Score should get swapped according to the change of Name in order that the record of any name in the resulted table is no different than that of the name in the original table.

So the result would be

```
Gender Name   Id       Score
f      Asuna  16383424 100  
m      Kirito 16354323 98   
m      Kurain 16349834 59   
f      Sirika 16325352 60   

```

# Details

You might miss a lot if you are unwilling to read the details.

## Table

Four fixed columns: Gender, Name, Id and Score

- Gender: only 'f' and 'm', representing "female" and "male". When sorted by, females come above of males.
- Name: a string consisting of at most six letters. They are sorted in lexicographical order. If you don't know the word just remember to use ``strncmp``.
- Id: a distinct 8-digit integer. It should be sorted in ascending order. If you find two same id in the input, you might want to report to your TA. That's definitely a bug.
- Score: an integer ranging from 0 to 100. Hardly can people get full marks. Note that score is sorted in descending order.

In the case where two records have the same Gender, Name or Score and need to be sorted by one of them, sort the two records by Id instead.

If the following table is sorted by Gender

```
Gender Name   Id       Score
f      Asuna  16383424 100  
m      Kurain 16349834 59   
m      Kirito 16354323 98   
f      Sirika 16325352 60   

```

The result would be this. Note that Asuna and Sirika are all females and the two records are sorted by Id in ascending order.

```
Gender Name   Id       Score
f      Sirika 16325352 60   
f      Asuna  16383424 100  
m      Kurain 16349834 59   
m      Kirito 16354323 98   

```

## Input

The first line is an positive integer ``n`` indicating the number of rows in the four-column table.

The following ``n`` lines are the body of the table. We don't know the maximum value of ``n``, but don't worry. Recall ``malloc`` or ``calloc`` you've learned.

The rest consists of some lines representing the queries from the user to sort and print a table by specific column

Each of the rest lines consists of an integer (called ``query number``) from \\( \lbrace-1, 0, 1, 2, 3, 4\rbrace \\)

- -1 means the end of the queries. Exit the program.
- 0 means printing the original table (the table from the input, not sorted by any columns)
- 1 means sorting the table by Gender and printing the resulted table
- 2 means sorting the table by Name and printing the resulted table
- 3 means sorting the table by Id and printing the resulted table
- 4 means sorting the table by Score and printing the resulted table

### Sample Input

```
4
f Asuna  16383424 100  
m Kurain 16349834 59   
m Kirito 16354323 98   
f Sirika 16325352 60   
0
1
2
3
4
-1

```

### Explanation

Original Table

```
Gender Name   Id       Score
f      Asuna  16383424 100  
m      Kurain 16349834 59   
m      Kirito 16354323 98   
f      Sirika 16325352 60   

```

Query number:

```
0      ---- original table
1      ---- sort the table by Gender
2      ---- sort the table by Name
3      ---- sort the table by Id
4      ---- sort the table by Score
-1     ---- quit

```


## Output

Each row contains 6 + 1 + 6 + 1 + 8 + 1 + 5 characters and a new line ``\n``

If a name contains less than six characters, such as "Asuna", it should be formatted to have six characters by filling in the right some extra spaces: "Asuan ". It is the same for other columns.

There is a blank line between two printed tables. That means there are two ``\n`` after the last cell of each table, even for the last printed table.

Check out the following sample output for more information

### Sample Output

```
Gender Name   Id       Score
f      Asuna  16383424 100  
m      Kurain 16349834 59   
m      Kirito 16354323 98   
f      Sirika 16325352 60   

Gender Name   Id       Score
f      Sirika 16325352 60   
f      Asuna  16383424 100  
m      Kurain 16349834 59   
m      Kirito 16354323 98   

Gender Name   Id       Score
f      Asuna  16383424 100  
m      Kirito 16354323 98   
m      Kurain 16349834 59   
f      Sirika 16325352 60   

Gender Name   Id       Score
f      Sirika 16325352 60   
m      Kurain 16349834 59   
m      Kirito 16354323 98   
f      Asuna  16383424 100  

Gender Name   Id       Score
f      Asuna  16383424 100  
m      Kirito 16354323 98   
f      Sirika 16325352 60   
m      Kurain 16349834 59   


```

Note: There should be three spaces and two ``\n``s after the "59" on the last line.

# Hint

Use ``struct`` to represent a record, let ``pointers`` to the records engage in the sorting instead of swapping the real records (otherwise it would be time consuming), and utilize ``qsort_s`` (``qsort_r`` on Ubuntu) to help share you work. (Hint of Hint: The fifth parameter can be the query numbers)
