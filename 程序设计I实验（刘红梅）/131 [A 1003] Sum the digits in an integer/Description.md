# [A 1003] Sum the digits in an integer

# Description

Write a program that reads an integer with 3 digits and adds all the digits in the integer.For example,if an integer is 932,the sum of all its digits is 9+3+2=14.

# Input

An integer x.(100<=x<=999)

# Output

The sum of all x's digits

# Sample Input

```
932
```

# Sample Output

```
14
```

# Hint

Use the % operator(求余) to extract digits, and use the / operator(取整除法) to remove the extracted digit. For instance,932 % 10 = 2 and 932 / 10 = 93.