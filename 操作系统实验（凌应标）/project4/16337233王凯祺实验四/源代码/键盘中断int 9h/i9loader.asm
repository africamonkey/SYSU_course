extrn _int_9_main:near   ;声明一个c程序函数int_9_main

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
	mov  ax,  0980h
	;mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS
	call near ptr _int_9_main
	
	in al, 61h				; get value of keyboard control lines
	mov ah, al				; save it
	or al, 80h				; set the 'enable kbd' bit
	out 61h, al				; and write it out the control port
	xchg ah, al				; fetch the origin control port value
	out 61h, al				; and write it back
	; http://webpages.charter.net/danrollins/techhelp/0106.HTM
	
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
