org 100h

	push ds
	push es
	mov ax,cs
	mov es,ax
	mov ds,ax
	mov ax,1
	int 21h
	mov ax,2
	int 21h
	mov ax,3
	int 21h
	mov ax,4
	int 21h
	int 22h
	int 23h
	int 24h
	pop es
	pop ds
	retf