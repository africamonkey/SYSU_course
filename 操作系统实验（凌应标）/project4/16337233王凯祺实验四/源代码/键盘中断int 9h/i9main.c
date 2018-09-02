int tx = 15, ty = 24;

void yan_ge_putchar(char c, int ttx, int tty) {
	char x, y;
	int pos;
	
	/* store origin position */ 
	asm mov ah, 03h
	asm mov bx, 0
	asm int 10h
	asm mov x, dh
	asm mov y, dl
	
	/* set position */ 
	asm mov ah, 02h
	asm mov bh, 0
	asm mov dh, ttx
	asm mov dl, tty
	asm int 10h
	
	/* write letter */
	asm mov ah, 0ah
	asm mov al, c
	asm mov bh, 0
	asm mov cx, 1
	asm int 10h

	/* restore origin position */
	asm mov ah, 02h
	asm mov bh, 0
	asm mov dh, x
	asm mov dl, y
	asm int 10h
}

int_9_main(){
	char x;
	asm in al, 60h
	asm mov x, al
	tx = (tx * 83 + 79) % 23;
	ty = (ty * 83 + 79) % 71;
	yan_ge_putchar('o', tx, ty+0);
	yan_ge_putchar('u', tx, ty+1);
	yan_ge_putchar('c', tx, ty+2);
	yan_ge_putchar('h', tx, ty+3);
	yan_ge_putchar('!', tx, ty+4);
}

