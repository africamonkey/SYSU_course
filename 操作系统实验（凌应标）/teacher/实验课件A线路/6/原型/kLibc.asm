.8086

_TEXT segment byte public 'CODE'
DGROUP group _TEXT,_DATA,_BSS
assume cs:_TEXT

extrn _Function_Num
extrn _Lower_to_Upper
extrn _StringLen
extrn _StringLen2
extrn _Num
extrn _Print_Int
extrn _Bin_to_Dec


Start:
Public _Load_Int21
_Load_Int21 proc
    push ax
	push bx
	push cx
	push dx
	push es
	push ds
	
    xor ax,ax
	mov es,ax
	mov word ptr es:[33*4],offset Int21_All
	mov ax,cs
	mov word ptr es:[33*4+2],ax

	pop ax
	mov ds,ax
	pop ax
	mov es,ax
	pop dx
	pop cx
	pop bx
	pop ax
	ret
_Load_Int21 endp

; ***************************************
;* 21h Interrupt                        *
; ***************************************
Int21_All:
	push bx
	push cx
	push dx
	push es
	push ds
	
	cmp ah,0
	jz case00
	cmp ah,1
	jz case01
	cmp ah,2
	jz case02
	cmp ah,3
	jz case03
	cmp ah,4
	jz case04
	cmp ah,5
	jz case05
	cmp ah,6
	jz case06
	cmp ah,7
	jz case07
	cmp ah,8
	jz case08
	
case00:
    call Int21_Fun00
	jmp Int21_End
case01:
    call Int21_Fun01
	jmp Int21_End
case02:
    call Int21_Fun02
	jmp Int21_End
case03:
    call Int21_Fun03
	jmp Int21_End
case04:
    call Int21_Fun04
	jmp Int21_End
case05:
    call Int21_Fun05
	jmp Int21_End
case06:
    call Int21_Fun06
	jmp Int21_End
case07:
    call Int21_Fun07
	jmp Int21_End
case08:
    call Int21_Fun08
	jmp Int21_End 
	
Int21_End:
    pop dx
	mov ds,dx
	pop dx
	mov es,dx
	pop dx
	pop cx
	pop bx
	iret
	
; ***************************************
;* Fun00  of   21h
; ***************************************
Int21_Fun00:
    mov ax,0b800h
	mov es,ax
	mov ah,0ah
	mov al,'O'
	mov es:[((80*10+35)*2)],ax
	mov al,'r'
	mov es:[((80*10+36)*2)],ax
	mov al,'c'
	mov es:[((80*10+37)*2)],ax
	mov al,'h'
	mov es:[((80*10+38)*2)],ax
	mov al,'!'
	mov es:[((80*10+39)*2)],ax
	mov al,'O'
	mov es:[((80*10+40)*2)],ax
	mov al,'r'
	mov es:[((80*10+41)*2)],ax
	mov al,'c'
	mov es:[((80*10+42)*2)],ax
	mov al,'h'
	mov es:[((80*10+43)*2)],ax
	mov al,'!'
	mov es:[((80*10+44)*2)],ax
	ret
; ***************************************
;* Fun01  of   21h
; ***************************************
Int21_Fun01:
    mov si,dx
    push dx
	mov dx,bx
	mov bx,0
Loop01:
    cmp byte ptr [si],97
	jl continue01
	cmp byte ptr [si],122
	jg continue01
	sub byte ptr [si],32
	jmp continue01
continue01:
    mov cx,si
	inc cx
	mov si,cx
	inc bx
    cmp bx,dx
	jnz Loop01
	pop dx
    ret

; ***************************************
;* Fun02  of   21h
; ***************************************
Int21_Fun02:
    mov si,dx
    push dx
	mov dx,bx
	mov bx,0
Loop02:
    cmp byte ptr [si],65
	jl continue02
	cmp byte ptr [si],90
	jg continue02
	add byte ptr [si],32
	jmp continue02
continue02:
    mov cx,si
	inc cx
	mov si,cx
	inc bx
    cmp bx,dx
	jnz Loop02
	pop dx
    ret

; ***************************************
;* Fun03  of   21h
; ***************************************
Int21_Fun03:
    mov si,dx
	push dx
	mov dx,bx
	mov bx,0
	mov cx,0
Loop03:
    push dx
    mov ax,1
	mov dx,cx
mul03:
    inc ax
	add cx,dx
	cmp ax,10
	jnz mul03
	
    mov dl,byte ptr[si]
	sub dl,48
	mov dh,0
	add cx,dx
	
	inc bx
	mov ax,si
	inc ax
	mov si,ax
	pop dx
	cmp bx,dx
	jnz Loop03
	
	pop dx
	mov ax,cx
    ret
	
; ***************************************
;* Fun04  of   21h
; ***************************************	
Int21_Fun04:
    push bx
	call near ptr _Print_Int
	pop bx
    ret
	
; ***************************************
;* Fun05  of   21h
; ***************************************
Int21_Fun05:
    mov si,dx
	push dx
	push es
    mov ax,0b800h
	mov es,ax
	mov dx,bx
	mov bx,0
Loop05:
    push dx
    mov al,80
	mul ch
	
	mov bp,ax
	mov dl,cl
	mov dh,0
	add bp,dx
	add bp,bp
	
	mov ah,0Bh
	mov al,byte ptr[si]
	mov es:[bp],ax
	
	inc si
	inc bx
	inc cl
	pop dx
	cmp bx,dx
	jnz Loop05
	
	pop ax
	mov es,ax
	pop dx
    ret

; ***************************************
;* Fun06  of   21h
; ***************************************	
Int21_Fun06:
    mov si,dx
	push dx
	
	call near ptr _Bin_to_Dec
	
	pop dx
    ret
	
; ***************************************
;* Fun07  of   21h
; ***************************************	
Int21_Fun07:
    mov si,dx
	push dx
	push es
    mov ax,0b800h
	mov es,ax
	mov dx,bx
	mov bx,0
	
	mov ah,01h
Loop07:
    push dx
    push ax
    mov al,80
	mul ch
	
	mov bp,ax
	mov dl,cl
	mov dh,0
	add bp,dx
	add bp,bp
	
	pop ax
	mov al,byte ptr[si]
	mov es:[bp],ax
	
	inc ah
	cmp ah,0Fh
	jg ini
next:
	inc si
	inc bx
	inc cl
	pop dx
	cmp bx,dx
	jnz Loop07
	
	pop ax
	mov es,ax
	pop dx
    ret

ini:
    mov ah,01h
	jmp next

; ***************************************
;* Fun08  of   21h
; ***************************************	
Int21_Fun08:
    push dx
	push cx
	
	cmp cx,dx
	jnz UnEqual
	
	mov dx,0
Loop08:
    mov bl,byte ptr [si]
	cmp bl,byte ptr [bp]
	jnz UnEqual
	
	inc si
	inc bp
	inc dx
	cmp dx,cx
	jnz Loop08
	jmp Equal
Equal:
	pop cx
	pop dx
	mov ax,1
    ret
UnEqual: 
	pop cx
	pop dx
	mov ax,0
    ret
	
public _Show_Orch
_Show_Orch proc
    push ax
    push bx
    push cx
    push dx
    push es
    push bp
	push si
	
    mov ah,0
	int 21h
	
	pop si
    pop bp
    pop ax
    mov es,ax
    pop dx
    pop cx
    pop bx
    pop ax
	ret
_Show_Orch endp

public _Fun_Upper
_Fun_Upper proc 

	push ax
    push bx
    push cx
    push dx
    push es
    push bp
	mov	bp,sp
	push si
    mov	si,word ptr [bp+14]
	
    mov ah,1
    mov dx,si
	mov bx,word ptr [_StringLen]
    int 21h
	
	pop si
    pop bp
    pop ax
    mov es,ax
    pop dx
    pop cx
    pop bx
    pop ax
    ret
_Fun_Upper endp


public _Fun_Lower
_Fun_Lower proc 

	push ax
    push bx
    push cx
    push dx
    push es
    push bp
	mov	bp,sp
	push si
    mov	si,word ptr [bp+14]
	
    mov ah,2
    mov dx,si
	mov bx,word ptr [_StringLen]
    int 21h
	
	pop si
    pop bp
    pop ax
    mov es,ax
    pop dx
    pop cx
    pop bx
    pop ax

    ret
_Fun_Lower endp

public _String_to_Num
_String_to_Num proc
    push bx
    push cx
    push dx
    push es
    push bp
	mov	bp,sp
	push si
    mov	si,word ptr [bp+12]
	
    mov ah,3
    mov dx,si
	mov bx,word ptr [_StringLen]
    int 21h
	
	pop si
    pop bp
    pop dx
    mov es,dx
    pop dx
    pop cx
    pop bx
	ret
_String_to_Num endp

public _Num_to_String
_Num_to_String proc
	push ax
    push bx
    push cx
    push dx
    push es
    push bp
	mov	bp,sp
	push si
    mov	si,word ptr [bp+14]
	
	mov ah,4
	mov bx,si
	int 21h
	
	pop si
    pop bp
    pop ax
    mov es,ax
    pop dx
    pop cx
    pop bx
    pop ax
	ret
_Num_to_String endp

public _Print_String
_Print_String proc
	push ax
    push bx
    push cx
    push dx
    push es
    push bp
	mov	bp,sp
	push si
	
    mov	si,word ptr [bp+14]
	mov ax,word ptr [bp+16]
	mov bx,word ptr [bp+18]
	
	mov ch,al
	mov cl,bl
    mov ah,5
    mov dx,si
	mov bx,word ptr [_StringLen]
    int 21h
	
	pop si
    pop bp
    pop ax
    mov es,ax
    pop dx
    pop cx
    pop bx
    pop ax
	ret
_Print_String endp



public _Binary_to_Decimal
_Binary_to_Decimal proc
	push ax
    push bx
    push cx
    push dx
    push es
    push bp
	mov	bp,sp
	push si
    mov	si,word ptr [bp+14]
	
    mov ah,6
    mov dx,si
    int 21h
	
	pop si
    pop bp
    pop ax
    mov es,ax
    pop dx
    pop cx
    pop bx
    pop ax
	ret
_Binary_to_Decimal endp


public _Print_CoLor_String
_Print_CoLor_String proc
	push ax
    push bx
    push cx
    push dx
    push es
    push bp
	mov	bp,sp
	push si
	
    mov	si,word ptr [bp+14]
	mov ax,word ptr [bp+16]
	mov bx,word ptr [bp+18]
	mov ch,al
	mov cl,bl

    mov ah,7
    mov dx,si
	mov bx,word ptr [_StringLen]
    int 21h
	
	pop si
    pop bp
    pop ax
    mov es,ax
    pop dx
    pop cx
    pop bx
    pop ax
	ret
_Print_CoLor_String endp

public _If_Equal
_If_Equal proc
    push bx
    push cx
    push dx
    push es
    push bp
	mov	bp,sp
	push si
	
	mov	si,word ptr [bp+12]
	mov dx,si
	mov	si,word ptr [bp+14]
	mov bp,dx
	
	mov cx,word ptr [_StringLen]
	mov dx,word ptr [_StringLen2]
	mov ah,8
	int 21h
	
	pop si
    pop bp
    pop bx
    mov es,bx
    pop dx
    pop cx
    pop bx
	ret
_If_Equal endp 


_TEXT ends
_DATA segment word public 'DATA'
_DATA ends
_BSS segment word public 'BSS'
_BSS ends
end start