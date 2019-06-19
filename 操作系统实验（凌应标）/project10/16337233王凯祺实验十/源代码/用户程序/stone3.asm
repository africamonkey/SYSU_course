; 程序源代码（stone.asm）
; 本程序在文本方式显示器上从左边射出一个*号,以45度向右下运动，撞到边框后反射,如此类推.
;  凌应标 2014/3
;  王凯祺 2018/3
;  NASM汇编格式
	delay  equ 50000					; 计时器延迟计数,用于控制画框的速度
	ddelay equ 580					; 计时器延迟计数,用于控制画框的速度
	sx     equ 13
	sy     equ 0
	wx     equ 12
	wy     equ 39
	org 100h					; 程序加载到100h，可用于生成COM
	
start:
	mov ax,cs
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov ax,0B800h				; 文本窗口显存起始地址
	mov gs,ax					; GS = B800h

loop1:
	dec word[count]				; 递减计数变量
	jnz loop1					; >0：跳转;
	mov word[count],delay
	dec word[dcount]				; 递减计数变量
	jnz loop1
	mov word[count],delay
	mov word[dcount],ddelay
	
	dec word[timess]
	jnz skip_end
	jmp end
	
skip_end:
	xor dx, dx
	mov word ax, [t]
	xor bx, bx
	mov word bx, wx
	add bx, bx
	sub bx, 2
	div bx
	cmp dx, wx
	jb xok
	sub bx, dx
	mov dx, bx
xok:
	add dx, sx
	mov word [x], dx
	
	xor dx, dx
	mov word ax, [t]
	xor bx, bx
	mov word bx, wy
	add bx, bx
	sub bx, 2
	div bx
	cmp dx, wy
	jb yok
	sub bx, dx
	mov dx, bx
yok:
	add dx, sy
	mov word [y], dx
	
show:	
	xor dx, dx
	mov word ax, [t]
	mov bx, 15
	div bx
	mov cx, dx
	add cx, 1
	xor ax,ax                 ; 计算显存地址
	mov ax,word[x]
	mov bx,80
	mul bx
	add ax,word[y]
	mov bx,2
	mul bx
	mov bx,ax
	mov ah,cl				;  0000：黑底、1111：亮白字（默认值为07h）
	mov al,byte[char]			;  AL = 显示字符值（默认值为20h=空格符）
	mov [gs:bx],ax  		;  显示字符的ASCII码值
	inc word [t]
	
	mov ah, 03h
	mov bx, 0
	int 10h
	mov [cursorx], dh
	mov [cursory], dl
	
	mov ah, 13h
	mov al, 1
	mov bl, 0eh
	mov bh, 0
	mov dh, 10
	mov dl, 30
	mov bp, namemsg
	mov cx, 18
	int 10h
	
	mov ah, 13h
	mov al, 1
	mov bl, 0eh
	mov bh, 0
	mov dh, 11
	mov dl, 27
	mov bp, exitmsg
	mov cx, 25
	int 10h
	
	mov ah, 02h
	mov bh, 0
	mov dh, [cursorx]
	mov dl, [cursory]
	int 10h
	
	jmp loop1

end:
	retf

datadef:	
	count dw delay
	dcount dw ddelay
	t    dw 0
	x    dw 0
	y    dw 0
	cursorx	db 0
	cursory	db 0
	timess dw 250

	char db 'A'
	
	namemsg db '16337233 WangKaiqi'
	exitmsg db 'Wait a moment to exit ...'
