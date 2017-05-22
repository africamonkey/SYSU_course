# 公共前缀

# Description

共同前缀是指两个字符串开头相同的部分。

例如：abcd和abe的共同前缀是ab；abcd和ABCD没有共同前缀。

实现一个函数，统计两个字符串(长度都不超过50）的最长公共前缀，如果没有共同前缀，则输出“no common prefix”。

函数声明：

```c
char * prefix(char* s1, char* s2);
```
 
 ## 注意：只用实现prefix即可，main函数已定义

# Sample Input

```
abcdqwer   abcqwer
```
 

# Sample Output

```
abc
```

# Hint

注意：应当使用malloc函数申请新的内存空间来作为返回值。在main函数的末尾处会使用free来释放这些内存。

函数原型

```c

void *malloc(int size);

void free(void *block);
```

