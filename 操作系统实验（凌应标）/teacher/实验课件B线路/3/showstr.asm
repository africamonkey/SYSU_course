;程序源代码（showstr.asm）
extrn _upper:near   ;声明一个c程序函数upper
extrn _Message:near      ;声明一个外部变量
.8086
_TEXT segment byte public 'CODE'
DGROUP group _TEXT,_DATA,_BSS
       assume cs:_TEXT
org 100h
start:
	mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS
	mov  ss,  ax           ; SS = cs
	mov  sp, 100h    
	call near ptr _upper
	mov	bp, offset _Message ; BP=当前串的偏移地址
	mov	ax, ds			    ; ES:BP = 串地址
	mov	es, ax			    ; 置ES=DS 
	mov	 cx, 10         	; CX = 串长（=10）
	mov	 ax, 1301h	 
	; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	 bx, 0007h
	; 页号为0(BH = 0) 黑底白字(BL = 07h)
	mov  dh, 20		; 行号=10
	mov	 dl, 10		; 列号=10
	int	10h		; BIOS的10h功能：显示一行字符
	jmp $

_TEXT ends
;************DATA segment*************
_DATA segment word public 'DATA'
_DATA ends
;*************BSS segment*************
_BSS	segment word public 'BSS'
_BSS ends
;**************end of file***********
end start
