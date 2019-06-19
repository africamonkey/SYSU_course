void putchar(char c) {
	asm mov ah, 02h
	asm mov dl, c
	asm int 21h
}

void puts_no_new_line(const char* s) {
	int i = 0;
	for (; s[i] != '\000'; ++i) {
		putchar(s[i]);
	}
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
	putchar(13);
}