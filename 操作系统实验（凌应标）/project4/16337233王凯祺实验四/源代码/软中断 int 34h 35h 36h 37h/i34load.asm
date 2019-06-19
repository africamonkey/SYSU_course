extrn _int_34_main:near   ;声明一个c程序函数int_34_main

.8086
_TEXT segment byte public 'CODE'
DGROUP group _TEXT,_DATA,_BSS
       assume cs:_TEXT
org 0100h
start:
	push ax
	push bx
	push cx
	push dx
	push ds
	push es
	mov  ax,  0d00h
	;mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS
	call near ptr _int_34_main

	mov al, 20h
	out 20h, al
	
	pop es
	pop ds
	pop dx
	pop cx
	pop bx
	pop ax
	iret

_TEXT ends
;************DATA segment*************
_DATA segment word public 'DATA'
_DATA ends
;*************BSS segment*************
_BSS	segment word public 'BSS'
_BSS ends
;**************end of file***********
end start
