extrn _main:near   ;声明一个c程序函数main
extrn _timeint:near
extrn _create_kernel_process:near
extrn _ax_save:word
extrn _bx_save:word
extrn _cx_save:word
extrn _dx_save:word
extrn _si_save:word
extrn _di_save:word
extrn _bp_save:word
extrn _es_save:word
extrn _ds_save:word
extrn _ss_save:word
extrn _sp_save:word
extrn _ip_save:word
extrn _cs_save:word
extrn _flags_save:word

.8086
_TEXT segment byte public 'CODE'
DGROUP group _TEXT,_DATA,_BSS
       assume cs:_TEXT
org 0100h
start:
	mov  ax,  0a00h
	;mov  ax,  cs
	mov  ds,  ax           ; DS = CS
	mov  es,  ax           ; ES = CS
	mov  ss,  ax           ; SS = cs
	mov  sp,  100h
	
	call near ptr _create_kernel_process
	
	push ds
	mov ax, 0h
	mov ds, ax
	mov bx, 20h
	mov ax, offset timeint
	mov [bx], ax
	mov bx, 22h
	mov ax, es
	mov [bx], ax
	pop ds
	
	call near ptr _main
	jmp $
	
timeint:
	cli
	
	push ds					; StackTop: *\flags\cs\ip\ds(user)
	push cs					; StackTop: *\flags\cs\ip\ds(user)\cs(kernel)
	pop ds					; StackTop: *\flags\cs\ip\ds(user)
							; ds <- kernel cs
	mov _ax_save, ax		; Save ax
	pop ax					; StackTop: *\flags\cs\ip
							; ax <- ds(user)
	mov _ds_save, ax		; Save ds
	pop ax					; StackTop: *\flags\cs
	mov _ip_save, ax		; Save ip
	pop ax					; StackTop: *\flags
	mov _cs_save, ax		; Save cs
	pop ax					; StackTop: *
	mov _flags_save, ax		; Save flags
	
	mov _bx_save, bx		; Save bx
	mov _cx_save, cx		; Save cx
	mov _dx_save, dx		; Save dx
	mov _si_save, si		; Save si
	mov _di_save, di		; Save di
	mov _bp_save, bp		; Save bp
	mov ax, es
	mov _es_save, ax		; Save es
	mov ax, ss
	mov _ss_save, ax		; Save ss
	mov _sp_save, sp		; Save sp
	
	mov ax, 0a00h
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0h
	
	call near ptr _timeint
	
	mov sp, _sp_save		; Restore sp
	mov ax, _ss_save
	mov ss, ax				; Restore ss
	mov ax, _es_save
	mov es, ax				; Restore es
	mov bp, _bp_save		; Restore bp
	mov di, _di_save		; Restore di
	mov si, _si_save		; Restore si
	mov dx, _dx_save		; Restore dx
	mov cx, _cx_save		; Restore cx
	mov bx, _bx_save		; Restore bx
	mov ax, _flags_save
	push ax					; Restore flags
	mov ax, _cs_save
	push ax					; Restore cs
	mov ax, _ip_save
	push ax					; Restore ip
	mov ax, _ds_save
	push ax
	mov ax, _ax_save		; Restore ax
	pop ds					; Restore ds
	
	push ax
	mov al,20h			; AL = EOI
	out 20h,al			; 发送EOI到主8529A
	out 0A0h,al			; 发送EOI到从8529A
	pop ax
	sti
	iret


_TEXT ends
;************DATA segment*************
_DATA segment word public 'DATA'
_DATA ends
;*************BSS segment*************
_BSS	segment word public 'BSS'
_BSS ends
;**************end of file***********
end start
