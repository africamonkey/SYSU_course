# Sort the string

## Description
Given a list of strings, sort and output them in ascending order(using strcmp).

## Input
The first line is an integer n(1 <= n <= 1000), indicating the number of strings. In the following n lines are n strings(no more than 100 characters, contains no space) to be sorted.

## Output
The strings in ascending order.

## Sample Input
```
5
ZGW
ZD
CJ
LSC
PB
```
## Sample Output
```
CJ
LSC
PB
ZD
ZGW
```

## Hint

本题使用普通排序算法可以过

改进的方法，有兴趣的同学可以了解一下用trie树做字符串排序，可以将时间复杂度降到O（n）

[字符串排序](http://dongxicheng.org/structure/trietree/)
