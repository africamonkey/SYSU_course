
extrn _cmain:near
.8086

_TEXT segment byte public 'CODE'
DGROUP group _TEXT,_DATA,_BSS
	assume cs:_TEXT

	org 100h
start:
	xor ax,ax
	mov es,ax
	mov word ptr es:[51*4],offset Orch
	mov ax,cs
	mov word ptr es:[51*4+2],ax
	
	xor ax,ax
	mov es,ax
	mov word ptr es:[52*4],offset OS
	mov ax,cs
	mov word ptr es:[52*4+2],ax
	
	xor ax,ax
	mov es,ax
	mov word ptr es:[53*4],offset HAHA
	mov ax,cs
	mov word ptr es:[53*4+2],ax
	
	xor ax,ax
	mov es,ax
	mov word ptr es:[54*4],offset final
	mov ax,cs
	mov word ptr es:[54*4+2],ax

	mov  ax,  cs
	mov  ds,  ax           	; DS = CS
	mov  es,  ax           	; ES = CS
	mov  ss,  ax           	; SS = cs
	mov  sp,  100h   		;SP指向本段高端－4
	call near ptr _cmain    ;调用C语言程序cfname()
	jmp $

	include kliba.asm       ;包含内核库过程kliba.asm
_TEXT ends
_DATA segment word public 'DATA'
_DATA ends
_BSS segment word public 'BSS'
_BSS ends
end start