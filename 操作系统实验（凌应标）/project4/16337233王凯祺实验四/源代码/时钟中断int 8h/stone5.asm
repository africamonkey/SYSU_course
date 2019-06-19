; 程序源代码（stone.asm）
; 本程序在文本方式显示器上从左边射出一个*号,以45度向右下运动，撞到边框后反射,如此类推.
;  凌应标 2014/3
;  王凯祺 2018/3
;  NASM汇编格式
	delay  equ 4					; 计时器延迟计数,用于控制画框的速度
	sx     equ 0
	sy     equ 77
	wx     equ 25
	wy     equ 3
	org 100h					; 程序加载到100h，可用于生成COM
	
start:
	push ds
	push es
	mov ax,940h
	mov ds,ax
	mov es,ax
	mov ax,0B800h				; 文本窗口显存起始地址
	mov gs,ax					; GS = B800h
loop1:
	dec word[count]				; 递减计数变量
	jnz end				; >0：跳转;
	mov word[count],delay
	
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

end:
	pop es
	pop ds
	mov al,20h			; AL = EOI
	out 20h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	iret			; 从中断返回

datadef:	
	count dw delay
	t    dw 0
	x    dw 0
	y    dw 0

	char db 'A'