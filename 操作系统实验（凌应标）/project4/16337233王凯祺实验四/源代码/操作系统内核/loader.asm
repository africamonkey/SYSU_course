extrn _main:near   ;声明一个c程序函数main
.8086
_TEXT segment byte public 'CODE'
DGROUP group _TEXT,_DATA,_BSS
       assume cs:_TEXT
org 0100h
start:
	mov  ax,  0a00h
	;mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS
	mov  ax,  0c00h
	mov  ss,  ax           ; SS = cs
	mov  sp, 0ffffh
	call near ptr _main
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
