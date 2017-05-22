# 汉诺塔

# Description
> 汉诺塔是学习递归的一个入门题目。汉诺塔(3个木桩的编号从左往右为1-3)的游戏规则：

1、 每次只允许移动一个盘子

2、 移动盘子时，编号大的盘子不能移动到编号小的盘子上面，也就是要保持每根木桩上的盘子从上到下都是递增的（任何编号的盘子都能直接移动到空的木桩上）

要求：将所有盘子从木桩1移动到木桩3

# Input
> 第一行是一个数字t，表示有t个测试用例

> 接下来的t行每一行是一个数字n，表示初始状态有n个盘子在木桩1上

# Output
对于每一个用例，输出完成游戏的所有操作，每个移动操作占一行

# Simple Input
1

3

# Simple Output
move disk 1 from peg 1 to peg 3

move disk 2 from peg 1 to peg 2

move disk 1 from peg 3 to peg 2

move disk 3 from peg 1 to peg 3

move disk 1 from peg 2 to peg 1

move disk 2 from peg 2 to peg 3

move disk 1 from peg 1 to peg 3
