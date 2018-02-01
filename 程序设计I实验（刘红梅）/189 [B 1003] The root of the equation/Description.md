# [B 1003] The root of the equation

# Description

从键盘读入三个数a, b, c，输出方程![](http://latex.codecogs.com/svg.latex?ax^2+bx+c=0)的两个实根。

# Input

三个数a,b,c， 保证方程为一元二次方程，且一定有两个实根。

# Outpt

方程![](http://latex.codecogs.com/svg.latex?ax^2+bx+c=0)的两个实根，小根在前，大根在后， 结果保留到小数点后三位。

# Sample Input

```
1 -4 3
```

# Sample Output

```
1.000 3.000
```

# Hint

求平方根可用&lt;math.h&gt;中的sqrt函数