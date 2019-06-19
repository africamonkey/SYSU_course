
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                              klib.asm
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


; 导入全局变量
extern	_disp_pos



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
    	mov bp,sp
		;***
        mov ax,0b800h
		mov es,ax
		mov al,byte ptr [bp+2+2+2+2] ;ch\IP\bp\es\ax
		mov ah,00Fh
		mov di,[_disp_pos]
		mov	es:[di], ax
		add	[_disp_pos], 2
		;***
		mov sp,bp
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
    	mov ax,0b800h
		mov es,ax
		mov	bp, sp

		mov	si, word ptr [bp + 2+2+2+2]	; pszInfo\IP\bp\es\ax
		mov	di, word ptr [_disp_pos]
		mov	ah, 0Fh
	.1:
		mov al,byte ptr [si]
		inc si
		mov byte ptr [di],al
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
    pop ax
	pop es
	pop	bp
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
	pop	bp
	ret
_cprintf endp
; ========================================================================
;                  void _port_out(u16 port, u8 value);
; ========================================================================
Public	_port_out
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
Public	_port_in
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
