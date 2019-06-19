; 程序源代码（stone.asm）
; 本程序在文本方式显示器上从左边射出一个字符串'16337233WangKaiqi',以45度向右下运动，撞到边框后反射,如此类推.
; 凌应标 2014/3
; 王凯祺 2018/3
; NASM汇编格式
	Dn_Rt equ 1                  ;D-Down,U-Up,R-right,L-Left
	Up_Rt equ 2                  ;
	Up_Lt equ 3                  ;
	Dn_Lt equ 4                  ;
	delay equ 50000					; 计时器延迟计数,用于控制画框的速度
	ddelay equ 580					; 计时器延迟计数,用于控制画框的速度

org 100h

section .data
	count dw delay
	dcount dw ddelay
	rdul db Dn_Rt         ; 向右下运动
	x    dw 7
	y    dw 0
	char db 'A'
	message db '16337233WangKaiqi'

section .text
	
start:
	mov word [x], 7
	mov word [y], 0
	mov byte [char], 'A'
	mov byte [rdul], Dn_Rt
	mov word [count], delay
	mov word [dcount], ddelay
	mov si, message
	mov byte [si], '1'
	inc si
	mov byte [si], '6'
	inc si
	mov byte [si], '3'
	inc si
	mov byte [si], '3'
	inc si
	mov byte [si], '7'
	inc si
	mov byte [si], '2'
	inc si
	mov byte [si], '3'
	inc si
	mov byte [si], '3'
	inc si
	mov byte [si], 'W'
	inc si
	mov byte [si], 'a'
	inc si
	mov byte [si], 'n'
	inc si
	mov byte [si], 'g'
	inc si
	mov byte [si], 'K'
	inc si
	mov byte [si], 'a'
	inc si
	mov byte [si], 'i'
	inc si
	mov byte [si], 'q'
	inc si
	mov byte [si], 'i'
	
	;xor ax,ax					; AX = 0   程序加载到0000：100h才能正确执行
	mov ax,0B800h				; 文本窗口显存起始地址
	mov gs,ax				        ; GS = 0xB800h
	mov byte[char],'A'
loop1:
	dec word[count]				; 递减计数变量
	jnz loop1					; >0：跳转;
	mov word[count],delay
	dec word[dcount]				; 递减计数变量
	jnz loop1
	mov word[count],delay
	mov word[dcount],ddelay

	mov al,1
	cmp al,byte[rdul]
	jz  DnRt
	mov al,2
	cmp al,byte[rdul]
	jz  UpRt
	mov al,3
	cmp al,byte[rdul]
	jz  UpLt
	mov al,4
	cmp al,byte[rdul]
	jz  DnLt
	jmp $	

DnRt:
	inc word[x]
	inc word[y]
	mov bx,word[x]
	mov ax,25
	sub ax,bx
	jz  dr2ur
	mov bx,word[y]
	mov ax,63
	sub ax,bx
	jz  dr2dl
	jmp show
dr2ur:
	mov word[x],23
	mov byte[rdul],Up_Rt	
	jmp show
dr2dl:
	mov word[y],62
	mov byte[rdul],Dn_Lt	
	jmp show

UpRt:
	dec word[x]
	inc word[y]
	mov bx,word[y]
	mov ax,63
	sub ax,bx
	jz  ur2ul
	mov bx,word[x]
	mov ax,-1
	sub ax,bx
	jz  ur2dr
	jmp show
ur2ul:
	mov word[y],62
	mov byte[rdul],Up_Lt	
	jmp show
ur2dr:
	mov word[x],1
	mov byte[rdul],Dn_Rt	
	jmp show	
	
UpLt:
	dec word[x]
	dec word[y]
	mov bx,word[x]
	mov ax,-1
	sub ax,bx
	jz  ul2dl
	mov bx,word[y]
	mov ax,-1
	sub ax,bx
	jz  ul2ur
	jmp show

ul2dl:
	mov word[x],1
	mov byte[rdul],Dn_Lt	
	jmp show
ul2ur:
	mov word[y],1
	mov byte[rdul],Up_Rt	
	jmp show
	
DnLt:
	inc word[x]
	dec word[y]
	mov bx,word[y]
	mov ax,-1
	sub ax,bx
	jz  dl2dr
	mov bx,word[x]
	mov ax,25
	sub ax,bx
	jz  dl2ul
	jmp show

dl2dr:
	mov word[y],1
	mov byte[rdul],Dn_Rt	
	jmp show
	
dl2ul:
	mov word[x],23
	mov byte[rdul],Up_Lt	
	jmp show
	
show:
	mov byte ah,0
	mov byte al,0
	mov bx,0
	mov cx,2000
black:
	mov [gs:bx],ax
	inc bx
	inc bx
	loop black
	
	xor ax,ax                 ; 计算显存地址
	mov word ax,[x]
	mov bx,80
	mul bx
	add word ax,[y]
	mov bx,2
	mul bx
	mov bx,ax
	mov si, message
	mov cx, 17
print_str:
	mov byte ah,0Fh				;  0000：黑底、1111：亮白字（默认值为07h）
	mov byte al,[si]			;  AL = 显示字符值（默认值为20h=空格符）
	mov [gs:bx],ax  		;  显示字符的ASCII码值
	inc si
	inc bx
	inc bx
	loop print_str
	jmp loop1
	
end:
    jmp $                   ; 停止画框，无限循环 
