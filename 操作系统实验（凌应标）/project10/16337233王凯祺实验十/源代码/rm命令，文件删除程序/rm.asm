extrn _rmmain:near   ;声明一个c程序函数rmmain

.8086
_TEXT segment byte public 'CODE'
DGROUP group _TEXT,_DATA,_BSS
       assume cs:_TEXT
org 0100h
start:
	mov ax, cs
	mov ds, ax
	mov es, ax
	mov ss, ax
	call near ptr _rmmain

_TEXT ends
;************DATA segment*************
_DATA segment word public 'DATA'
_DATA ends
;*************BSS segment*************
_BSS	segment word public 'BSS'
_BSS ends
;**************end of file***********
end start
