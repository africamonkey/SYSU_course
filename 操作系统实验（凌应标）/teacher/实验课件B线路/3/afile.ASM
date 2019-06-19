
extern  macro %1    ;统一用extern导入外部标识符
	extrn %1
endm


extern _cmain:near
extern _ccch:near
extern _buffer:near



.8086
_TEXT segment byte public 'CODE'
assume cs:_TEXT
DGROUP group _TEXT,_DATA,_BSS
org 100h


start:
		mov ax,cs
		mov ds,ax; DS = CS
		mov es,ax; ES = CS
		mov ss,ax; SS = cs
		mov sp, 100h    
;        inc  byte ptr [_ccch]		
		mov  byte ptr [_buffer],'Q'
		mov  byte ptr [_buffer+1],'Q'
		mov  byte ptr [_buffer+2],'Q'
		call near ptr _cmain
    	jmp $	


		
		
		
		include kliba.asm



_TEXT ends

_DATA segment word public 'DATA'

_DATA ends

_BSS	segment word public 'BSS'
_BSS ends

end start
