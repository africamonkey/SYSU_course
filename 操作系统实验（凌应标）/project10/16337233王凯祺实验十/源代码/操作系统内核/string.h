int strlen(char *s) {
	int i = 0;
	while (s[i]) ++i;
	return i;
}

int strcmp(char *a, char *b) {
	int la = strlen(a);
	int lb = strlen(b);
	int i = 0;
	for (; i < la || i < lb; ++i)
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	return 0;
}

int prefix_match(char *text, char *pattern) {
	int la = strlen(pattern);
	int lb = strlen(text);
	int i = 0;
	if (la > lb) return 0;
	for (; i < la; ++i)
		if (text[i] != pattern[i]) return 0;
	return text[la] <= 32;
}

void strcpy_from_ds_ip(int filename_ds, char *filename, int cs1, int ip1) {
	char w;
	int i;
	for (i = 0; i < 12; ++i) {
		asm push ds
		asm mov ax, cs1
		asm mov ds, ax
		asm mov bx, ip1
		asm mov al, [bx]
		asm mov w, al
		asm pop ds
		asm push ds
		asm mov ax, filename_ds
		asm mov ds, ax
		*filename = w;
		asm pop ds
		if (w == 0x00) break;
		++ ip1;
		++ filename;
	}
}