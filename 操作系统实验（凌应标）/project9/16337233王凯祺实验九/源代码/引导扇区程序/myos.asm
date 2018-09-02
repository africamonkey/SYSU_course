;程序源代码（myos1.asm）
org  7c00h		; BIOS将把引导扇区加载到0:7C00h处，并开始执行

	jmp short Start                      ; Jump, 2 Bytes
	nop                                  ; 1 Bytes
	BS_OEMName DB 'AM-OS9.0'             ; OEM String, 8 Bytes
	BPB_BytsPerSec DW 512
	BPB_SecPerClus DB 1
	BPB_RsvdSecCnt DW 1
	BPB_NumFATs DB 2
	BPB_RootEntCnt DW 224
	BPB_TotSec16 DW 2880
	BPB_Media DB 0xF0
	BPB_FATSz16 DW 9
	BPB_SecPerTrk DW 18
	BPB_NumHeads DW 2
	BPB_HiddSec DD 0
	BPB_TotSec32 DD 0
	BS_DrvNum DB 0
	BS_Reserved1 DB 0
	BS_BootSig DB 29h
	BS_VolID DD 16337233h
	BS_VolLab DB 'AM-OS 9.0  '           ; 11 Bytes
	BS_FileSysType DB 'FAT12   '         ; 8 Bytes

FATMem equ 2000h
KernelCS equ 0a00h
KernelIP equ 0100h

Start:
                                       
LoadFAT:
	;读软盘或硬盘上的若干物理扇区到内存的ES:BX处：
	mov word bx, FATMem
	mov es, bx
	xor bx, bx
	mov ah,2                 ; 功能号
	mov al,33                ;扇区数
	mov dl,0                 ;驱动器号 ; 软盘为0，硬盘和U盘为80H
	mov dh,0                 ;磁头号 ; 起始编号为0
	mov ch,0                 ;柱面号 ; 起始编号为0
	mov cl,1                 ;起始扇区号 ; 起始编号为1
	int 13H ;                调用读磁盘BIOS的13h功能
	; FAT 根目录已加载到指定内存区域 0x2000:0x0000 中
	
getFAT:
;  Output: if LOADER.COM found in [file_num], return dx = [start sector], bx = [size]
;          otherwise, dx = 0
	
	xor dx, dx                 ; dx = 0
	mov ax, 2600h
	xor cx, cx                 ; cx = 0
	
FATfindLoop:
	xor bx, bx
	mov ds, bx
	mov [axbak], ax
	push ax
	push cx
	mov ax, KernelStr          ; ax = addr("KERNEL  BIN")
	xor cx, cx                 ; cx = 0
	
KernelStrMatch:
	push ax
	xor ax, ax
	mov ds, ax
	mov bx, [axbak]
	mov ax, FATMem
	mov ds, ax
	pop ax
	add bx, cx                 ; the cx-th bit
	mov bl, [bx]
	push ax
	xor ax, ax
	mov ds, ax
	mov byte [char1], bl
	pop ax

	mov bx, ax
	mov bl, [bx]	
	cmp bl, [char1]
	jnz KernelNotMatch
	
	inc ax
	inc cx
	cmp cx, 11
	jb KernelStrMatch
	xor bx, bx
	mov ds, bx
	mov dx, [axbak]            ; matched, dx = kernel addr
KernelNotMatch:
	
	pop cx
	pop ax
	add ax, 20h
	inc cx
	cmp dx, 0
	jnz KernelOK
	cmp cx, 224
	jb FATfindLoop
	call dispStr
	jmp $
	
KernelOK:
	; dx = kernel addr
	call dispStr
	add dx, 1ah
	mov bx, dx
	mov ax, FATMem
	mov ds, ax
	mov dx, [bx]                ; dx = first cluster
	
	mov ax, KernelIP
go_and_fetch:
	call copy_sector
	call find_next_sector
	add ax, 200h
	cmp dx, 0ff8h
	jb go_and_fetch
	
	mov ax, KernelCS
	mov bx, KernelIP
	shl ax, 4
	add bx, ax
	jmp bx
	
dispStr:
	push dx
	xor bx, bx
	mov es, bx
	mov ax, kernel_not_found
	mov cx, 16
	cmp dx, 0
	jz skip
	mov ax, kernel_found
	mov cx, 25
skip:
	mov bp, ax
	mov ax, 01301h
	mov bx, 000ch
	mov dx, 0000h
	int 10h
	pop dx
	ret	
	
copy_sector:
; Input: dx = cluster number
;        ax = memory offset
;        (KernelCS is DS)
	push ax
	push dx
	xor bx, bx
	mov ds, bx
	mov word [axbak], ax
	add dx, 31
	mov ax, dx
	xor dx, dx
	mov cx, 18
	div cx
	inc dx
	mov byte [qishishanqu], dl
	xor dx, dx
	mov cx, 2
	div cx
	mov byte [citou], dl
	mov byte [zhumian], al
	mov ax, KernelCS
	mov es, ax
	mov bx, [axbak]
	mov cl, [qishishanqu]
	mov ah, 2
	mov al, 1
	mov dl, 0
	mov dh, [citou]
	mov ch, [zhumian]
	int 13h
	
	pop dx
	pop ax
	ret
	
find_next_sector:
; Input: dx = cluster number
; Output: dx = next cluster number
	push ax
	mov bx, FATMem
	mov ds, bx
	mov ax, dx
	mov bx, dx
	xor dx, dx
	mov cx, 3
	mul cx
	mov cx, 2
	div cx
	add ax, 200h
	xor dx, dx
	test bx, 1h
	jnz odd_num
	; even_number
	mov bx, ax
	mov dl, [bx]
	inc bx
	mov dh, [bx]
	and dh, 0fh
	jmp even_odd_all_ok
odd_num:
	; odd number
	mov bx, ax
	mov dl, [bx]
	inc bx
	mov dh, [bx]
	shr dl, 4
	mov cl, dh
	and cl, 0fh
	shl cl, 4
	add dl, cl
	shr dh, 4
even_odd_all_ok:
	pop ax
	ret
	
AfterRun:
	qishishanqu db 0
	citou db 0
	zhumian db 0
	KernelStr db 'LOADER  COM'
	axbak dw 0
	char1 db 0
	kernel_not_found db "Kernel Not Found"
	kernel_found     db "Kernel Found, Starting..."
	times 510-($-$$) db 0
	db 0x55,0xaa
