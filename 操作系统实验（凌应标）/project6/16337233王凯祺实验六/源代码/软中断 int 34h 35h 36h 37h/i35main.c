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

void yan_ge_puts(const char* s, int ttx, int tty) {
	int i = 0;
	for (; s[i] != '\000'; ++i) {
		yan_ge_putchar(s[i], ttx, tty + i);
	}
}

int_35_main(){
	yan_ge_puts("I am int 35h", 6, 10 + 40);
	yan_ge_puts("16337233 Wangkaiqi", 7, 10 + 40);
}

