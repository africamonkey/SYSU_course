##################################################
#                                                #
#        purpose:to swap two values              #
#                                                #
###############  text segment ####################

.text
.globl main
main:    
   la   $t0,  number    # 读取两个整数的首地址放入$t0
   lw   $t1,  0($t0)    # 读0-3字节内容存入$t1
   lw   $t2,  4($t0)    # 读4-7字节内容存入$t2

   li   $v0,  4         # 输出字符串msg1
   la   $a0,  msg1
   syscall

   li   $v0,  1         # 1号 功能调用，输出整型数据
   move $a0,  $t1       # 
   syscall

   li   $v0,  4         # 打印msg2
   la   $a0,  msg2
   syscall

   li   $v0,  1         # 1号 功能调用，输出整型数据
   move $a0,  $t2
   syscall

   move $t3,  $t1       # 交换$t1和$t2
   move $t1,  $t2       #
   move $t2,  $t3       #

   li   $v0,  4         # 输出字符串msg3
   la   $a0,  msg3
   syscall

   li   $v0,  1         # 输出整型数据，输出交换后的数据  
   move $a0,  $t1
   syscall

   li   $v0,  4         # 输出字符串
   la   $a0,  msg4      # 换行符 \n
   syscall

   li   $v0,  1         # 输出整型数据，输出交换后的数据
   move $a0,  $t2
   syscall

   li $v0, 10           # 退出
   syscall


########### data segment  ##############
.data
   number:  .word 12,34
   msg1:    .asciiz  "the first number is:"
   msg2:    .asciiz  "\nthe second number is:"
   msg3:    .asciiz  "\nnow they are swapped as:\n"
   msg4:    .ascii   "\n"

## end of file


