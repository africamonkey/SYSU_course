;8086CPU的MASM/TASM汇编语言程序调用Turbo C语言程序，生成.com形式代码的基本模版
；凌应标 2014/3

extern  macro %1    ;统一用extern导入外部标识符
	extrn %1
endm

;导入C中的全局函数或全局变量,本例中导入了3个
extern _cmain:near  ;导入C中的主函数main()
extern _ccch:near   ;导入C中的一个函数ccch()
extern _buffer:near ;导入C中的外部变量buffer



.8086
_TEXT segment byte public 'CODE'
assume cs:_TEXT
DGROUP group _TEXT,_DATA,_BSS
org 100h


start:
		mov ax,cs;准备设置有关的段寄存器
		mov ds,ax; DS = CS
		mov es,ax; ES = CS
		mov ss,ax; SS = cs
		mov sp, 0xFFF0h ;栈顶在段内高端，留空了16单元   
;汇编预处理安排在这里
    	jmp $	
;利用包含伪指令，将一些内核汇编语言过程文件纳入本程序，如本例中kliba.asm文件		
		include kliba.asm

_TEXT ends

_DATA segment word public 'DATA'

_DATA ends

_BSS	segment word public 'BSS'
_BSS ends

end start
