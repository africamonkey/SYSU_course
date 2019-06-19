org 100h			; 程序加载到100h，可用于生成COM
; 设置时钟中断向量（08h），初始化段寄存器
	xor ax,ax			; AX = 0
	mov es,ax			; ES = 0
	mov word [es:20h],Timer	; 设置时钟中断向量的偏移地址
	mov ax,cs 
	mov word [es:22h],ax		; 设置时钟中断向量的段地址=CS
	mov ds,ax			; DS = CS
	mov es,ax			; ES = CS
; 在屏幕右下角显示字符‘!’	
	mov	ax,0B800h		; 文本窗口显存起始地址
	mov	gs,ax		; GS = B800h
	mov ah,0Fh		; 0000：黑底、1111：亮白字（默认值为07h）
	mov al,'!'			; AL = 显示字符值（默认值为20h=空格符）
	mov [gs:((80*12+39)*2)],ax	; 屏幕第 24 行, 第 79 列
	jmp $			; 死循环
; 时钟中断处理程序
	delay equ 4		; 计时器延迟计数
	count db delay		; 计时器计数变量，初值=delay
Timer:
	dec byte [count]		; 递减计数变量
	jnz end			; >0：跳转
	inc byte [gs:((80*12+39)*2)]	; =0：递增显示字符的ASCII码值
	mov byte[count],delay		; 重置计数变量=初值delay
end:
	mov al,20h			; AL = EOI
	out 20h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	iret			; 从中断返回
