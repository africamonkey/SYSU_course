extrn _upper:near   ;声明一个c程序函数upper
extrn _pro2:near
extrn _cmd:near
extrn _bb:near
extrn _ttime:near
extrn _ddate:near
extrn _CMDline:near
extrn _Message:near      ;声明一个外部变量
extrn _aanum:near
extrn _aa:near
extrn _disp_pos::near
extrn _cpointer::near
extrn _CMDline::near
extrn _int34::near
extrn _int35::near
extrn _int36::near
extrn _int37::near
extrn _CurrentProc::near
extrn _select::near

.8086
_TEXT segment byte public 'CODE'
DGROUP group _TEXT,_DATA,_BSS
       assume cs:_TEXT
org 100h

start:
	
    mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS
	mov  ss,  ax           ; SS = cs
	mov  sp, 100h

	jmp inivector


@1:
    call near ptr _pro2
    call near ptr _cmd
  
	mov  ax,0600h
    mov  bx,0700h
	mov  cx,0h
	mov  dx,184fh
        int  10h
	jmp @1
   	jmp $

Message:
      db 'Welcome to use OS-v3 system      '
MessageLength  equ ($-Message)

Message1:
      db 'you can input some legal instructions. h for help'
MessageLength1  equ ($-Message1)

public _lprintf
_lprintf proc
    push    ds
    push    es
	mov	ax, cs	       ; 置其他段寄存器值与CS相同
	mov	ds, ax	       ; 数据段
	mov	bp, offset Message		 ; BP=当前串的偏移地址
	mov	ax, ds		 ; ES:BP = 串地址
	mov	es, ax		 ; 置ES=DS
	mov	cx, MessageLength  ; CX = 串长（=9）
	mov	ax, 1301h		 ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 009fh		 ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov dh, 0		       ; 行号=0
	mov	dl, 17			 ; 列号=0
	int	10h			 ; BIOS的10h功能：显示一行字符

    mov	bp, offset Message1
    mov	cx, MessageLength1
	mov	ax, 1301h
	mov	bx, 000fh
	mov dh, 2
	mov	dl, 3
	int	10h
    pop     es
    pop     ds
ret
_lprintf  endp

sycall:
	push ax
	mov ax,cs
	mov ds,ax
	mov es,ax
	pop ax
	dec ax
	jz in1
	dec ax
	jz in2
	dec ax
	jz in3
	dec ax
	jz in4
	dec ax
	jz in5
	jmp final
in1:
	call text1
	jmp final
in2:
	call near ptr _interupt2
	jmp final
in3:
	call near ptr _interupt3
	jmp final
in4:
	call near ptr _interupt4
	jmp final
in5:
	call near ptr _interupt5
	jmp final
final:
	mov al,20h			; AL = EOI
	out 20h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	iret				; 从中断返回

timeoffset dw ?
timebase dw ?	
inivector:
	push es
	mov ax,0
	mov es,ax
    mov [es:4*33], offset sycall
    mov [es:4*33+2], 9000h
	mov [es:4*34], offset text2
    mov [es:4*34+2], 9000h
	mov [es:4*35], offset text3
    mov [es:4*35+2], 9000h
	mov [es:4*36], offset text4
    mov [es:4*36+2], 9000h
	mov ax,[es:4*8]
	mov word ptr[timeoffset],ax
	mov ax,[es:4*8+2]
	mov word ptr[timebase],ax
	mov al,34h			; 设控制字值
	out 43h,al				; 写控制字到控制字寄存器
	mov ax,59659	; 每秒20次中断（50ms一次）
	out 40h,al				; 写计数器0的低字节
	mov al,ah				; AL=AH
	out 40h,al				; 写计数器0的高字节
	pop es
	jmp @1
	
public _lock
_lock proc
	push es
	push ax
	push ds
	mov ax,cs
	mov ds,ax
	mov ax,0
	mov es,ax
	mov ax,word ptr[timeoffset]
	mov [es:4*8],ax
	mov ax,word ptr[timebase]
	mov [es:4*8+2],ax
	pop ds
	pop ax
	pop es
	ret
_lock endp

public _unlock
_unlock proc
	push es
	push ax
	push ds
	mov ax,cs
	mov ds,ax
	mov ax,0
	mov es,ax
	mov ax,[es:4*8]
	mov word ptr[timeoffset],ax
	mov ax,[es:4*8+2]
	mov word ptr[timebase],ax
	mov [es:4*8], offset timer
    mov [es:4*8+2], 9000h
	pop ds
	pop ax
	pop es
	ret
_unlock endp
	
timer:
	cli
	call save
	call near ptr _select
	jmp restart
	
ds_save dw ?
ret_save dw ?
si_save dw ?
kernelsp dw ?	

public save
save proc
	push ds
	push cs
	pop ds
	pop word ptr [ds_save]
	pop word ptr [ret_save]
	mov word ptr[si_save],si
	mov si,word ptr [_CurrentProc]
	add si,22
	pop word ptr [si]
	add si,2
	pop word ptr [si]
	add si,2
	pop word ptr [si]
	mov word ptr [si-6],sp
	mov word ptr [si-8], ss
	mov si,ds
	mov ss,si
	mov sp,word ptr [_CurrentProc]
	add sp,18
	push word ptr[ds_save]
	push es
	push bp
	push di
	push word ptr[si_save]
	push dx
	push cx
	push bx
	push ax
	mov sp,word ptr[kernelsp]
	mov ax,word ptr [ret_save]
	jmp ax
save endp

lds_low dw ?
lds_high dw ?
restart  proc
	mov word ptr[kernelsp],sp
	mov sp,word ptr[_CurrentProc]
	pop ax
	pop bx
	pop cx
	pop dx
	pop si
	pop di
	pop bp
	pop es
	mov word ptr[lds_low],bx
	pop word ptr[lds_high]
	mov bx,sp
	mov bx,word ptr[bx]
	mov ss,bx
	mov bx,sp
	add bx,2
	mov sp,word ptr[bx]
	push word ptr[bx+6]
	push word ptr[bx+4]
	push word ptr[bx+2]
	lds bx,dword ptr[lds_low]
	push ax
	mov al,20h			; AL = EOI
	out 20h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	pop ax
	iret				; 从中断返回
restart  endp


public _ReadCommand
_ReadCommand proc
        push es
        push ds
		push cx
		push bx
		push ax
		push si
		push di
		mov cx,20
        mov bx,0b800h
		mov es,bx
        mov si,offset _CMDline
		mov di,650
readchar@1:   
		mov ah,0
        int 16h
        cmp al,0Dh
        jz  endcmd@1
		mov [si],al
		mov es:[di],al
        inc di
		mov byte ptr es:[di],0fh
        inc si
        inc di
        loop readchar@1
	
endcmd@1:
		pop	  di
		pop	  si
		pop	  ax
		pop	  bx
		pop	  cx
        pop   es
        pop   ds
        ret
_ReadCommand endp


Message31: db 'The time now is '
MessageLength31  equ ($-Message31)
Message32: db 'The date today is '
MessageLength32  equ ($-Message32)



public _time
_time proc
	push ds
    push es
	
    mov  ax,  cs
	mov  ds,  ax           ; DS = CS
    mov  ax,  cs
	mov  es,  ax           ; ES = Cs
	
    mov di,offset _ttime
	
	mov ah,02h
    int 1Ah
    mov al,ch
	mov ah,0
	mov bl,16
	div bl
	add al,30h
	mov [di],al

    mov ah,02h
    int 1Ah
    mov al,ch
and al,0fh
add al,30h
	mov [di+1],al
    mov byte ptr [di+2],' '
    mov byte ptr [di+3],'h'
	mov byte ptr [di+4],' '

	mov ah,02h
    int 1Ah
    mov al,cl
	mov ah,0
	mov bl,16
	div bl
	add al,30h
	mov [di+5],al

     mov ah,02h
     int 1Ah
     mov al,cl
     and al,0fh
     add al,30h
	mov [di+6],al
    mov byte ptr [di+7],' '
    mov byte ptr [di+8],'m'
	mov byte ptr [di+9],' '
    mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS	
	mov	bp, offset Message31		 ; BP=当前串的偏移地址
	mov	ax, ds		 ; ES:BP = 串地址
	mov	es, ax		 ; 置ES=DS
	mov	cx, MessageLength31 ; CX = 串长（=9）
	mov	ax, 1301h		 ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 000fh		 ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov 	dh, 10		       ; 行号=0
	mov	dl, 10			 ; 列号=0
	int	10h			 ; BIOS的10h功能：显示一行

    mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS
	mov	bp, offset _ttime ; BP=当前串的偏移地址
	mov	ax, ds			    ; ES:BP = 串地址
	mov	es, ax			    ; 置ES=DS 
	mov	 cx, 15         	; CX = 串长（=10）
	mov	 ax, 1301h	 
	; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	 bx, 000fh
	; 页号为0(BH = 0) 黑底白字(BL = 07h)
	mov  dh, 10		; 行号=10
	mov	 dl, 30		; 列号=10
	int	10h		; BIOS的10h功能：显示一行字符

        pop es
        pop ds
	ret
_time endp
public _mmdate
_mmdate proc

	push ds
    push es
    mov  ax,  cs
	mov  ds,  ax           ; DS = CS
    mov  ax,  cs
	mov  es,  ax           ; ES = Cs
	
	mov si,offset _ddate

	mov ah,04h
    int 1Ah
    mov al,cl
	mov ah,0
	mov bl,16
	div bl
	add al,30h
	mov [si],al

        mov ah,04h
        int 1Ah
        mov al,cl
        and al,0fh
	;mov cl,4	
        ;shr al,cl
        add al,30h
	mov [si+1],al

        mov byte ptr [si+2],' '
        mov byte ptr [si+3],'y'
	mov byte ptr [si+4],' '


	mov ah,04h
        int 1Ah
        mov al,dh
	mov ah,0
	mov bl,16
	div bl
	add al,30h
	mov [si+5],al

        mov ah,04h
        int 1Ah
        mov al,dh
        and al,0fh
	;mov cl,4	
        ;shr al,cl
        add al,30h
	mov [si+6],al

        mov byte ptr [si+7],' '
        mov byte ptr [si+8],'m'
	mov byte ptr [si+9],' '

	mov ah,04h
        int 1Ah
        mov al,dl
	mov ah,0
	mov bl,16
	div bl
	add al,30h
	mov [si+10],al

        mov ah,04h
        int 1Ah
        mov al,dl
        and al,0fh
	;mov cl,4	
        ;shr al,cl
        add al,30h
	mov [si+11],al

        mov byte ptr [si+12],' '
        mov byte ptr [si+13],'d'
	mov byte ptr [si+14],' '


        mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS	
	mov	bp, offset Message32		 ; BP=当前串的偏移地址
	mov	ax, ds		 ; ES:BP = 串地址
	mov	es, ax		 ; 置ES=DS
	mov	cx, MessageLength32 ; CX = 串长（=9）
mov	ax, 1301h		 ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 000fh		 ; 页号为0(BH = 0) 黑底白字(BL = 07h)
        mov 	dh, 10		       ; 行号=0
	mov	dl, 10			 ; 列号=0
	int	10h			 ; BIOS的10h功能：显示一行


        mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS
	mov	bp, offset _ddate ; BP=当前串的偏移地址
	mov	ax, ds			    ; ES:BP = 串地址
	mov	es, ax			    ; 置ES=DS 
	mov	 cx, 15         	; CX = 串长（=10）
	mov	 ax, 1301h	 
	; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	 bx, 000fh
	; 页号为0(BH = 0) 黑底白字(BL = 07h)
	mov  dh, 10		; 行号=10
	mov	 dl, 31		; 列号=10
	int	10h		; BIOS的10h功能：显示一行字符

        pop es
        pop ds
	ret
_mmdate endp


Message40: db 'please input a character: '
MessageLength40  equ ($-Message40)
Message50: db 'the ascii number of this character is:'
MessageLength50  equ ($-Message50)

public _lprintf2
_lprintf2 proc
	push ds
    push es

	mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS	
	mov	bp, offset Message40		 ; BP=当前串的偏移地址
	mov	ax, ds		 ; ES:BP = 串地址
	mov	es, ax		 ; 置ES=DS
	mov	cx, MessageLength40 ; CX = 串长（=9）
	mov	ax, 1301h		 ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 000fh		 ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov 	dh, 7		       ; 行号=0
	mov	dl, 10			 ; 列号=0
	int	10h			 ; BIOS的10h功能：显示一

        mov  ah,0
        int  16h
	mov  si,offset _aa
	mov  [si],al	

	mov bx,0b800h
	mov es,bx
	mov di,1192
	mov es:[di],al
        inc di
	mov byte ptr es:[di],0fh
        pop es
        pop ds

	ret
_lprintf2 endp


public _Low2Up
_Low2Up proc
	push ds
    push es
	mov si,offset _aanum

	mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS	
	mov	bp, offset Message50		 ; BP=当前串的偏移地址
	mov	ax, ds		 ; ES:BP = 串地址
	mov	es, ax		 ; 置ES=DS
	mov	cx, MessageLength50 ; CX = 串长（=9）
	mov	ax, 1301h		 ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 000fh		 ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov 	dh, 9		       ; 行号=0
	mov	dl, 10			 ; 列号=0
	int	10h			 ; BIOS的10h功能：显示一


    mov ax,[si]
	mov ah,0
	mov bl,16
	div bl
	add al,30h
	mov bx,0b800h
	mov es,bx
	mov di,1540
	mov es:[di],al
    inc di
mov byte ptr es:[di],0fh

        mov ax,[si]
        and al,0fh
        add al,30h
	mov bx,0b800h
	mov es,bx
	mov di,1542
	mov es:[di],al
        inc di
	mov byte ptr es:[di],0fh

        pop es
        pop ds
	ret
 _Low2Up endp 

Message60:
      db 'The programm has finished!'
MessageLength60  equ ($-Message60) 

public _reboot
_reboot proc
	push ds	
	push es
	mov	ax, cs	       ; 置其他段寄存器值与CS相同
	mov	ds, ax	       ; 数据段
	mov es, ax
	mov	bp, offset Message60		 ; BP=当前串的偏移地址
	mov	cx, MessageLength60 ; CX = 串长（=9）
	mov	ax, 1301h		 ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 000fh		 ; 页号为0(BH = 0) 黑底白字(BL = 07h)
        mov 	dh, 21		       ; 行号=0
	mov	dl, 10			 ; 列号=0
	int	10h			 ; BIOS的10h功能：显示一行
	
	mov ah,0
	int 16h

    pop  es
	pop  ds    
	ret
_reboot endp

Programeoffset dw 100h
Programebase   dw 8000h 
Tempoffset	   dw 0
Tempbase	   dw 0
BaseofPro1		dw 8000h
BaseofPro2		dw 7000h
BaseofPro3		dw 6000h
BaseofPro4		dw 5000h
BaseofPro5		dw 4000h

public _RunProm
_RunProm proc
	push bp
	push si
	mov bp,sp
	mov si,word ptr[bp+6]
	add si,si
	mov si,[BaseofPro1+si]
	mov word ptr[Programebase],si
	pop si
	pop bp
	call dword ptr [Programeoffset]
	ret
_RunProm endp

public _RunProm3
_RunProm3 proc
	push es
	push ax
	mov ax,0
	mov es,ax
	mov ax,[es:4*9]
	mov word ptr [Tempoffset],ax
	mov ax,[es:4*9+2]
	mov word ptr [Tempbase],ax
	mov [es:4*9], offset ouch
    mov [es:4*9+2], 9000h
	pop ax
	pop es
	call dword ptr [Programeoffset]
	push es
	push ax
	mov ax,0
	mov es,ax
	mov ax,word ptr [Tempbase]
    mov [es:4*9+2], ax
	mov ax,word ptr [Tempoffset]
    mov [es:4*9], ax
	pop ax
	pop es
    ret
_RunProm3 endp

Message80:
      db 'The fourth program run!'
MessageLength80  equ ($-Message80)

public _checkup
_checkup proc
	push ds	
	push es
mov	ax, cs	       ; 置其他段寄存器值与CS相同
	mov	ds, ax	       ; 数据段
	mov	bp, offset Message80		 ; BP=当前串的偏移地址
	mov	ax, ds		 ; ES:BP = 串地址
	mov	es, ax		 ; 置ES=DS
	mov	cx, MessageLength80 ; CX = 串长（=9）
	mov	ax, 1301h		 ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 000fh		 ; 页号为0(BH = 0) 黑底白字(BL = 07h)
        mov 	dh, 15		       ; 行号=0
	mov	dl, 10			 ; 列号=0
	int	10h			 ; BIOS的10h功能：显示一行
	pop  es
	pop  ds  
        ret

_checkup endp

BPB_SecPerTrk	DB 18
BS_DrvNum		DB 0
OffesetOfFile   equ 3000h
OffesetOfPro    equ 100h

public _loaderpro
_loaderpro proc
	push bp
	mov bp,sp
	push si
	mov si,word ptr[bp+8]
	add si,si
	mov ax,word ptr[BaseofPro1+si]
	mov es,ax
	pop si
	mov bx,OffesetOfPro
	mov ax,word ptr[bp+6]
	mov cx,200h
	mul cx
	add bx,ax
	mov ax,word ptr[bp+4]
	pop bp
	mov cl,1
	;mov word ptr[_cpointer],bx
	call	ReadSector
	ret
_loaderpro endp

public _loader
_loader proc
	push bp
	mov bp,sp
	mov ax,cs
	mov es,ax
	mov bx,OffesetOfFile
	mov ax,word ptr[bp+6]
	mov cx,200h
	mul cx
	add bx,ax
	mov ax,word ptr[bp+4]
	pop bp
	mov cl,1
	mov word ptr[_cpointer],bx
	call	ReadSector
	ret
_loader endp

public ReadSector
ReadSector proc
	push bp		; 保存BP
	mov bp, sp	; 让BP=SP
	sub	sp, 2 	; 辟出两个字节的堆栈区域保存要读的扇区数: byte [bp-2]
	mov	byte [bp-2], cl	; 压CL入栈（保存表示读入扇区数的传递参数）
	push bx			; 保存BX
	mov	bl, [BPB_SecPerTrk]	; BL=18（磁道扇区数）为除数
	div	bl			; AX/BL，商y在AL中、余数z在AH中
	inc	ah			; z ++（因磁盘的起始扇区号为1）
	mov	cl, ah		; CL <- 起始扇区号
	mov	dh, al		; DH <- y
	shr	al, 1		; y >> 1 （等价于y/BPB_NumHeads，软盘有2个磁头）
	mov	ch, al		; CH <- 柱面号
	and	dh, 1		; DH & 1 = 磁头号
	pop	bx			; 恢复BX
	; 至此，"柱面号、起始扇区、磁头号"已全部得到
	mov	dl, [BS_DrvNum]	; 驱动器号（0表示软盘A）
.GoOnReading: ; 使用磁盘中断读入扇区
	mov	ah, 2				; 功能号（读扇区）
	mov	al, byte [bp-2]		; 读AL个扇区
	int	13h				; 磁盘服务BIOS调用
	jc	.GoOnReading	; 如果读取错误，CF会被置为1，
						; 这时就不停地读，直到正确为止
	add	sp, 2			; 栈指针+2
	pop	bp				; 恢复BP
	ret
ReadSector endp

;****************************
; SCOPY@                    *
;****************************
;局部字符串带初始化作为实参问题补钉程序
public SCOPY@
SCOPY@ proc 
		arg_0 = dword ptr 6
		arg_4 = dword ptr 0ah
		push bp
			mov bp,sp
		push si
		push di
		push ds
			lds si,[bp+arg_0]
			les di,[bp+arg_4]
			cld
			shr cx,1
			rep movsw
			adc cx,cx
			rep movsb
		pop ds
		pop di
		pop si
		pop bp
		retf 8
SCOPY@ endp



;****************************
; void _cls()               *
;****************************

public _cls
_cls proc 
; 清屏
      push ax
      push bx
      push cx
      push dx		
      mov	ax, 600h	; AH = 6,  AL = 0
	mov	bx, 700h	; 黑底白字(BL = 7)
	mov	cx, 0		; 左上角: (0, 0)
	mov	dx, 184fh	; 右下角: (24, 79)
	int	10h		; 显示中断
	pop dx
	pop cx
	pop bx
	pop ax
      mov [_disp_pos],0
	ret
_cls endp

;********************************************************
; void _printChar(char ch)                            *
;********************************************************


public _printChar
_printChar proc 
    push bp
    push es
	push ax
	push di
    mov bp,sp
	;***
      mov ax,0b800h
	mov es,ax
	mov al,byte ptr [bp+2+2+2+2+2] ;ch\IP\bp\es\ax
	mov ah,00Fh
	mov di,[_disp_pos]
	mov	es:[di], ax
	add	[_disp_pos], 2
	;***
	;mov sp,bp
	pop di
    pop ax
	pop es
	pop bp
	ret
_printChar endp

;****************************
; void _getChar()           *
;****************************

public _getChar
_getChar proc
	mov ah,0
	int 16h
	ret
_getChar endp






; ========================================================================
;  void _printf(char * pszInfo);
; ========================================================================
Public	_printf
_printf proc
	push	bp         ;sp+2
	push	es         ;sp+2+2
	push    ax         ;sp+2+2+2
	push 	bx
	push 	si
	push	di
    mov ax,0b800h
	mov es,ax
	mov	bp, sp
	mov	si, word ptr [bp + 2+2+2+2+2+2+2]	; pszInfo\IP\bp\es\ax
	mov	di, word ptr [_disp_pos]
	mov	ah, 0Fh
	.1:
	mov al,byte ptr [si]
	inc si
	;mov byte ptr [di],al
	test	al, al
	jz	.2
	cmp	al, 0Ah	; 是回车吗?
	jnz	.3
	push	ax
	mov	ax, di
	mov	bl, 160
	div	bl
	and	ax, 0FFh
	inc	ax
	mov	bl, 160
	mul	bl
	mov	di, ax
	pop	ax
	jmp	.1
	.3:
	mov	es:[di], ax
	add	di, 2
	jmp	.1
 	.2:
	mov	[_disp_pos], di
	pop di
	pop si
	pop bx
    pop ax
	pop es
	pop bp
	ret
_printf endp
; ========================================================================
;                  void _cprintf(char * info, int color);
; ========================================================================
Public	_cprintf
_cprintf proc
	push	bp         ;sp+2
	push	es         ;sp+2+2
	push    ax         ;sp+2+2+2
    	mov ax,0b800h
	mov es,ax
	mov	bp, sp
	mov	si, word ptr [bp + 2+2+2+2]	; pszInfo\IP\bp\es\ax
	mov	di, word ptr [_disp_pos]
	mov	ah, byte ptr [bp +2+2+2+2]	; color
	.1@:
	mov al,byte ptr [si]
	inc si
	mov byte ptr [di],al
	test	al, al
	jz	.2@
	cmp	al, 0Ah	; 是回车吗?
	jnz	.3@
	push	ax
	mov	ax, di
	mov	bl, 160
	div	bl
	and	ax, 0FFh
	inc	ax
	mov	bl, 160
	mul	bl
	mov	di, ax
	pop	ax
	jmp	.1@
	.3@:
	mov	word ptr es:[di], ax
	add	di, 2
	jmp	.1@
	.2@:
	mov	word ptr [_disp_pos], di
      pop ax
	pop es
	pop bp
	ret
_cprintf endp
; ========================================================================
;                  void _port_out(u16 port, u8 value);
; ========================================================================
Public _port_out
_port_out proc
      push bp
      mov bp,sp
	mov	dx, word ptr [bp + 2]		; port
	mov	al, byte ptr [bp + 2 + 2]	; value
	out	dx, al
	nop	; 一点延迟
	nop
	mov sp,bp
	pop bp
	ret
_port_out endp
; ========================================================================
;                  u8 _port_in(u16 port);
; ========================================================================
Public _port_in
_port_in proc
      push bp
      mov bp,sp
      mov	dx, word ptr [bp + 2]		; port
	xor	ax, ax
	in	al, dx
	nop	; 一点延迟
	nop
	mov sp,bp
	pop bp
	ret
_port_in endp

str6 db "ouch! ouch!"
ouch:
	push ds	
	push es
	call _cls
	mov ax, 0b800h
	mov ax,cs ; 通过AX中转, 将CS的值传送给DS和ES
	mov ds,ax
	mov es,ax
	mov ah,13h ; 功能号
	mov al,1 ; 光标放到串尾
	mov bl,0ah ; 亮绿
	mov bh,0 ; 第0页
	mov dh,12 ; 第7行
	mov dl,37 ; 第54列
	mov bp,offset str6 ; BP=串地址
	mov cx,11 ; 串长为15个字符
	int 10h ; 调用10H号中断
	pop  es
	pop  ds  
    mov al,20h			; AL = EOI
	out 20h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	in al,60h
	iret				; 从中断返回

    Dn_Rt equ 1                  ;D-Down,U-Up,R-right,L-Left
    Up_Rt equ 2                  ;
    Up_Lt equ 3                  ;
    Dn_Lt equ 4                  ;
    delay equ 5000					; 计时器延迟计数,用于控制画框的速度
    ddelay equ 580					; 计时器延迟计数,用于控制画框的速度
	counter dw 100h
    count dw 5000
    dcount dw 580
    rdul db 1         ; 向右下运动
    x    dw 0
    y    dw 0
    char db 'A'
public text1
text1 proc
	push ds	
	push es
	mov ax,cs 
	mov ds,ax
	mov es,ax
	mov	ax,0B800h				; 文本窗口显存起始地址
	mov	es,ax					; GS = B800h
    mov byte ptr [char],'A'
loop1:
	dec word ptr [count]				; 递减计数变量
	jnz loop1					; >0：跳转;
	mov word ptr [count],delay
	dec word ptr [dcount]				; 递减计数变量
      jnz loop1
	mov word ptr [count],delay
	mov word ptr [dcount],ddelay

    mov al,1
    cmp al,byte ptr [rdul]
	jz  DnRt
      mov al,2
      cmp al,byte ptr [rdul]
	jz  UpRt
      mov al,3
      cmp al,byte ptr [rdul]
	jz  UpLts
      mov al,4
      cmp al,byte ptr [rdul]
	jz  DnLts
      jmp $	

DnRt:
	inc word ptr [x]
	inc word ptr [y]
	mov bx,word ptr [x]
	mov ax,12
	sub ax,bx
      jz  dr2ur
	mov bx,word ptr [y]
	mov ax,40 ;c
	sub ax,bx
      jz  dr2dl
	jmp show
dr2ur:
      mov word ptr [x],11
      mov byte ptr [rdul],Up_Rt	
      jmp show
dr2dl:
      mov word ptr [y],39 ;c
      mov byte ptr [rdul],Dn_Lt	
      jmp show
UpLts:
	jmp UpLt
DnLts:
	jmp DnLt
	  
UpRt:
	dec word ptr [x]
	inc word ptr [y]
	mov bx,word ptr [y]
	mov ax,40 ;c
	sub ax,bx
      jz  ur2ul
	mov bx,word ptr [x]
	mov ax,-1
	sub ax,bx
      jz  ur2dr
	jmp show
ur2ul:
      mov word ptr [y],39 ;c
      mov byte ptr [rdul],Up_Lt	
      jmp show
ur2dr:
      mov word ptr [x],1
      mov byte ptr [rdul],Dn_Rt	
      jmp show

	
	
UpLt:
	dec word ptr [x]
	dec word ptr [y]
	mov bx,word ptr [x]
	mov ax,-1
	sub ax,bx
      jz  ul2dl
	mov bx,word ptr [y]
	mov ax,-1
	sub ax,bx
      jz  ul2ur
	jmp show

ul2dl:
      mov word ptr [x],1
      mov byte ptr [rdul],Dn_Lt	
      jmp show
ul2ur:
      mov word ptr [y],1
      mov byte ptr [rdul],Up_Rt	
      jmp show

	
	
DnLt:
	inc word ptr [x]
	dec word ptr [y]
	mov bx,word ptr [y]
	mov ax,-1
	sub ax,bx
      jz  dl2dr
	mov bx,word ptr [x]
	mov ax,12
	sub ax,bx
      jz  dl2ul
	jmp show

dl2dr:
      mov word ptr [y],1
      mov byte ptr [rdul],Dn_Rt	
      jmp show
	
dl2ul:
      mov word ptr [x],11
      mov byte ptr [rdul],Up_Lt	
      jmp show

show:
      xor ax,ax                 ; 计算显存地址
      mov ax,word ptr [x]
	mov bx,80
	mul bx
	add ax,word ptr [y]
	mov bx,2
	mul bx
	mov bp,ax
	mov ah,0Fh				;  0000：黑底、1111：亮白字（默认值为07h）
	mov al,byte ptr [char]			;  AL = 显示字符值（默认值为20h=空格符）
	mov word ptr es:[bp],ax  		;  显示字符的ASCII码值
	dec word ptr [counter]
	jz  ending
	jmp loop1
	
	
ending:
	mov word ptr [counter],100h
    mov word ptr [count],5000
    mov word ptr [dcount],580
    mov byte ptr [rdul],1
    mov word ptr [x],0
	mov word ptr [y],0
    pop  es
	pop  ds  
    ret
text1 endp

str3 db "Welcome to my OS"
text2:
	push ds	
	push es
	mov ax, 0b800h
	mov ax,cs ; 通过AX中转, 将CS的值传送给DS和ES
	mov ds,ax
	mov es,ax
	mov ah,13h ; 功能号
	mov al,1 ; 光标放到串尾
	mov bl,0ah ; 亮绿
	mov bh,0 ; 第0页
	mov dh,6h ; 第7行
	mov dl,37h ; 第54列
	mov bp,offset str3 ; BP=串地址
	mov cx,16 ; 串长为15个字符
	int 10h ; 调用10H号中断
	pop  es
	pop  ds  
    mov al,20h			; AL = EOI
	out 20h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	iret				; 从中断返回
	
str4 db "SYSU"
str5 db "Computer Science"
text3:
	push ds	
	push es
	mov ax, 0b800h
	mov ax,cs ; 通过AX中转, 将CS的值传送给DS和ES
	mov ds,ax
	mov es,ax
	mov ah,13h ; 功能号
	mov al,1 ; 光标放到串尾
	mov bl,0ah ; 亮绿
	mov bh,0 ; 第0页
	mov dh,12h ; 第18行
	mov dl,12h ; 第18列
	mov bp,offset str4 ; BP=串地址
	mov cx,4 ; 串长为9个字符
	int 10h ; 调用10H号中断
	  mov ax,cs ; 通过AX中转, 将CS的值传送给DS和ES
	mov ds,ax
	mov es,ax
	mov ah,13h ; 功能号
	mov al,1 ; 光标放到串尾
	mov bl,0ah ; 亮绿
	mov bh,0 ; 第0页
	mov dh,13h ; 第19行
	mov dl,15 ; 第15列
	mov bp,offset str5 ; BP=串地址
	mov cx,16 ; 串长为9个字符
	int 10h ; 调用10H号中断
	pop  es
	pop  ds  
    mov al,20h			; AL = EOI
	out 20h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	iret				; 从中断返回
	
str1 db "14348047"
str2 db "Li Yanyue"
text4:
	push ds	
	push es
	mov ax, 0b800h
	mov ax,cs ; 通过AX中转, 将CS的值传送给DS和ES
	mov ds,ax
	mov es,ax
	mov ah,13h ; 功能号
	mov al,1 ; 光标放到串尾
	mov bl,0ah ; 亮绿
	mov bh,0 ; 第0页
	mov dh,12h ; 第18行
	mov dl,37h ; 第55列
	mov bp,offset str1 ; BP=串地址
	mov cx,8 ; 串长为9个字符
	int 10h ; 调用10H号中断
	  mov ax,cs ; 通过AX中转, 将CS的值传送给DS和ES
	mov ds,ax
	mov es,ax
	mov ah,13h ; 功能号
	mov al,1 ; 光标放到串尾
	mov bl,0ah ; 亮绿
	mov bh,0 ; 第0页
	mov dh,13h ; 第19行
	mov dl,37h ; 第55列
	mov bp,offset str2 ; BP=串地址
	mov cx,9 ; 串长为9个字符
	int 10h ; 调用10H号中断
	pop  es
	pop  ds  
    mov al,20h			; AL = EOI
	out 20h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	iret				; 从中断返回
	


_TEXT ends

;************DATA segment*************
_DATA segment word public 'DATA'
_DATA ends
;*************BSS segment*************
_BSS	segment word public 'BSS'
_BSS ends
;**************end of file***********
end start
