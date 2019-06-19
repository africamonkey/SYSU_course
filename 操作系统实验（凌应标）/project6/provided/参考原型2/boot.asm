org  7c00h		; BIOS将把引导扇区加载到0:7C00处，并开始执行
Start:
mov	ax, cs				; 置其他段寄存器值与CS相同
mov	ds, ax				; 数据段
mov	bp, Message		    ; BP=当前串的偏移地址
mov	ax, ds			    ; ES:BP = 串地址
mov	es, ax			    ; 置ES=DS
mov	cx, MessageLength 	; CX = 串长（=9）
mov	ax, 1301h			; AH = 13h（功能号）、AL = 01h（光标置于串尾）
mov	bx, 0007h			; 页号为0(BH = 0) 黑底白字(BL = 07h)
mov dh, 0	    		; 行号=0
mov	dl, 0	 			; 列号=0
int	10h		 			; BIOS的10h功能：显示一行字符
LoadKernal:
;读软盘或硬盘上的kernal到内存的ES:BX处：
mov ax, SegOfKernal  	;段地址 ; 存放数据的内存基地址
mov es,ax           	;设置段地址（不能直接mov es,段地址）
mov bx, OffSetOfKernal  ;偏移地址; 存放数据的内存偏移地址
mov ah,2              	;功能号
mov al, QTYofKernal   	;扇区数
mov dl,0          		;驱动器号 ; 软盘为0，硬盘和U盘为80H
mov dh,0          		;磁头号 ; 起始编号为0
mov ch,0          		;柱面号 ; 起始编号为0
mov cl,2       			;起始扇区号 ; 起始编号为1
int 13H 				;调用中断
;内核已加载到指定内存区域中
jmp SegOfKernal:OffSetOfKernal
jmp $             		;无限循环
Message:
    db 'Loading MyOs kernal...'
MessageLength  	equ ($-Message)
OffSetOfKernal  equ 100h
SegOfKernal    	equ 64*1024/16  ;第二个64k内存的段地址  
QTYofKernal 	equ 17  ;内核占用扇区数
times 510-($-$$)db	0	; 用0填充引导扇区剩下的空间
db 	55h, 0aah			; 引导扇区结束标志
