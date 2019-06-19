int fopen(const char *filename, const char *type) {
	int t1, t2;
	t1 = filename;
	t2 = type;
	asm mov bx, t1
	asm mov cx, t2
	asm mov dx, ds
	asm mov ah, 0h
	asm int 26h
}

int fgetbyte(int f_id, unsigned char *w) {
	int t = w;
	asm mov bx, f_id
	asm mov cx, t
	asm mov dx, ds
	asm mov ah, 1h
	asm int 26h
}

char fgetc(int f_id) {
	unsigned char w;
	int ret;
	ret = fgetbyte(f_id, &w);
	if (ret < 0) return -1;
	return w;
}

void fputbyte(int f_id, unsigned char w) {
	asm mov bx, f_id
	asm mov ah, 2h
	asm mov al, w
	asm int 26h
}

void fputc(int f_id, char w) {
	fputbyte(f_id, w);
}

void fclose(int f_id) {
	asm mov bx, f_id
	asm mov ah, 3h
	asm int 26h
}