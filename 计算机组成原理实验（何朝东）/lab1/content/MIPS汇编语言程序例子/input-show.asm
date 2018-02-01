############################################
#
# 输入一个数据---显示；输入一串字符---显示
#
#############################################

.data
    str:    .space 40                       # 分配40个字节空间
   msg1:    .asciiz  "\ninput a integer: "  # 
   msg2:    .asciiz  "\ninput a string: "   # 
   msg3:    .asciiz  "\nyou input: "        # 

.text
.globl main

main:              

   # 输入 integer
   li     $v0, 4                  # 显示信息 msg1
   la     $a0, msg1               
   syscall

   li     $v0, 5                  # 接收键盘输入的整数，并保存到$v0
   syscall                        # 
   move   $a1, $v0                # 将接收到的整数转存，$a1<-$v0                     

   li     $v0, 4                  # 显示 msg3
   la     $a0, msg3
   syscall

   li     $v0, 1                  # 显示 输入的整数
   move   $a0, $a1                # 显示的数必须保存到$a0
   syscall

   li     $v0, 4                  # 显示信息 msg2
   la     $a0, msg2
   syscall

   # 输入字符串 string
   li     $v0, 8                  # 接收键盘输入字符串
   la     $a0, str                # $a0<-字符串首地址(字符串缓冲区首地址）
   li     $a1, 40                 # 输入的字符串长度保存到$a1
   syscall

   li     $v0, 4                  # 显示输入的字符串 msg
   la     $a0, str
   syscall

   li     $v0, 10                 # 退出
   syscall                        # 系统调用
