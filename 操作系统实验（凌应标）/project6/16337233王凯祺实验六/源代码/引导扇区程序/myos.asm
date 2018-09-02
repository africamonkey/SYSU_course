;程序源代码（myos1.asm）
org  7c00h		; BIOS将把引导扇区加载到0:7C00h处，并开始执行
OffSetOfUserPrg1 equ 0a100h
Start:
	mov	ax, cs	       ; 置其他段寄存器值与CS相同
	mov	ds, ax	       ; 数据段
	mov	ax, ds		   ; ES:BP = 串地址
	mov	es, ax		   ; 置ES=DS
	
LoadnEx:
	;读软盘或硬盘上的若干物理扇区到内存的ES:BX处：
	mov bx, OffSetOfUserPrg1  ;偏移地址; 存放数据的内存偏移地址
	mov cx, bx
	mov ah,2                 ; 功能号
	mov al,17                 ;扇区数
	mov dl,0                 ;驱动器号 ; 软盘为0，硬盘和U盘为80H
	mov dh,0                 ;磁头号 ; 起始编号为0
	mov ch,0                 ;柱面号 ; 起始编号为0
	mov cl,2                 ;起始扇区号 ; 起始编号为1
	int 13H ;                调用读磁盘BIOS的13h功能
	; 用户程序a.com已加载到指定内存区域中
	jmp OffSetOfUserPrg1

AfterRun:
	jmp Start                      ;无限循环
	times 510-($-$$) db 0
	db 0x55,0xaa
