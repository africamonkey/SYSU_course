void putchar(char c) {
	char x, y;
	int pos;
	
	if (c >= 32) {
		asm mov ah, 0ah
		asm mov al, c
		asm mov bh, 0
		asm mov cx, 1
		asm int 10h
	}
	
	asm mov ah, 03h
	asm mov bx, 0
	asm int 10h
	asm mov x, dh
	asm mov y, dl
	
	if (c == 13)
		pos = (x + 1) * 80;
	else
		pos = x * 80 + y + 1;
	
	if (pos >= 2000) {
		asm mov ah, 06h
		asm mov al, 1
		asm mov bh, 07h
		asm mov dh, 24
		asm mov dl, 79
		asm mov ch, 0
		asm mov cl, 0
		asm int 10h
		pos -= 80;
	}
	x = pos / 80;
	y = pos % 80;
	
	asm mov ah, 02h
	asm mov bh, 0
	asm mov dh, x
	asm mov dl, y
	asm int 10h
}

char getchar() {
	char x;
	asm mov ah, 0
	asm int 16h
	asm mov x, al
	putchar(x);
	return x;
}

void gets(char *s) {
	char x = getchar();
	int i = 0;
	for (; x != 13; x = getchar())
		s[i++] = x;
	s[i++] = 0;
}

void puts(const char* s) {
	int i = 0;
	for (; s[i] != '\000'; ++i) {
		putchar(s[i]);
	}
	putchar(13);
}

void puts_no_new_line(const char* s) {
	int i = 0;
	for (; s[i] != '\000'; ++i) {
		putchar(s[i]);
	}
}

void puts_format(const char *s, int align) {
	int len = strlen(s);
	int i;
	if (len > align) align = len;
	align -= len;
	puts_no_new_line(s);
	for (i = 0; i < align; ++i)
		putchar(' ');
}

void printint(int x) {
	char st[11], tmp1, tmp2;
	int i, j, n;
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x == 0) {
		putchar('0');
	}
	for (i = 0; x > 0; ++i) {
		st[i] = x % 10 + '0';
		x = x / 10;
	}
	n = i;
	st[n] = '\000';
	for (i = n - 1; i >= 0; --i)
		putchar(st[i]);
	puts("");
}

void printhex(unsigned int x) {
	unsigned int y;
	char st[11], tmp1, tmp2;
	int i, j, n;
	putchar('0');
	putchar('x');
	if (x == 0) {
		putchar('0');
	}
	for (i = 0; x > 0; ++i) {
		y = x % 16;
		if (y < 10) st[i] = y + '0';
		else st[i] = (y - 10) + 'A';
		x = x / 16;
	}
	n = i;
	st[n] = '\000';
	for (i = n - 1; i >= 0; --i)
		putchar(st[i]);
	puts("");
}

void printint_format(int x, int align) {
	char st[11], t;
	int i, n;
	if (x < 0) {
		x = -x;
		putchar('-');
		-- align;
	}
	if (x == 0) {
		putchar('0');
		-- align;
	}
	for (i = 0; x > 0; ++i) {
		st[i] = x % 10 + '0';
		x = x / 10;
	}
	n = i;
	st[n] = '\000';
	for (i = n - 1; i >= 0; --i)
		putchar(st[i]);
	puts_format("", align - n);
}