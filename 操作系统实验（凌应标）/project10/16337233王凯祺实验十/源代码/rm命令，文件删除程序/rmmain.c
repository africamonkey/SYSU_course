#include "stdlib.h"
#include "stdio.h"
#include "file.h"

void rmmain() {
	char src[20];
	char w;
	int f_src, my_ds;
	asm mov ax, ss
	asm mov my_ds, ax
	src[0] = 0;
	getParameter(my_ds, src);
	f_src = fopen(src, "d");
	if (f_src >= 0) {
	} else
	if (f_src == -1) {
		puts("error: file not found");
		exit(0);
	} else
	if (f_src == -2) {
		puts("error: file is being occupied");
		exit(0);
	} else
	if (f_src == -3) {
		puts("error: no enough space");
		exit(0);
	} else
	if (f_src == -4) {
		puts("error: unknown open method");
		exit(0);
	} else {
		puts("error: unknown error");
		exit(0);
	}
	while ((w = fgetc(f_src)) != -1) {
		putchar(w);
	}
	fclose(f_src);
	exit(0);
}