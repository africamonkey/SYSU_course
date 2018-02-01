###################################################
#
# 从键盘输入三个整数，计算三数之和，并找出最大数
#
###########################################################
.text
.globl main

main:
   la $t0, array        # 数组首地址
   li $v0, 4            # 输出字符串
   la $a0, msg1         # 输出信息msg1
   syscall

   li $v0, 5            # 接收键盘输入一整数，并保存到$v0
   syscall
   sw $v0,0($t0)        # 将键盘输入第一个数据保存到数组中

   li $v0, 5
   syscall
   sw $v0,4($t0)        # 将键盘输入第二个数据保存到数组中

   li $v0, 5
   syscall
   sw $v0,8($t0)        # 将键盘输入第三个数据保存到数组中

   lw $s0, ($t0)        # 从数组中读取第一个数保存到$s0寄存器中
   lw $s1, 4($t0)       # 从数组中读取第二个数保存到$s0寄存器中
   lw $s2, 8($t0)       # 从数组中读取第三个数保存到$s0寄存器中

   add $s3, $s0, $s1    # 
   add $s4, $s2, $s3    # 三数之和保存到$s4

   li $v0, 4            # 
   la $a0, msg3         # 输出信息msg3
   syscall

   li $v0, 1            # 输出整数
   move $a0, $s4        # 三数之和
   syscall

   li $v0, 4            # 换行
   la $a0, newline
   syscall

   blt $s0, $s1,num2    # if $s0<$s1, 转 num2
   move $s3, $s0        # 

   j num3               # if $s0>=$s1, 转 num3
num2:
   move $s3, $s1        # if $s1>=$s0,$s3<-$s1

num3:
   bge $s3, $s2, num4   # if $3>=$s2, $s3已是最大数，转 num4
   move $s3, $s2        # 否则，$s2是最大数，保存到$s3

num4:    # 输出最大数
   li $v0, 4            # 输出字符串
   la $a0, msg2         # 输出信息msg2
   syscall

   li $v0, 1            # 输出整数
   move $a0, $s3        # 输出最大数
   syscall

   li $v0, 4            # 输出字符串
   la $a0, newline      # 换行
   syscall

   li $v0, 10           # 退出
   syscall               

.data
   array:       .space     12  # 分配12个字节空间（存放三个字数）
   msg1:        .asciiz    "input the 3 integers(each num end of [enter]): \n"
   msg2:        .asciiz    "the max num is: "
   msg3:        .asciiz    "the tatal is: "
   newline:     .asciiz    "\n"     # 换行符
