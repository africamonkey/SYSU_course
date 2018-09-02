#include "stdlib.h"
#include "stdio.h"
#include "file.h"

void cpmain() {
	char src[48], dst[20];
	unsigned char w;
	int f_src, f_dst, my_ds, i, j;
	
	asm mov ax, ss
	asm mov my_ds, ax
	src[0] = 0;
	getParameter(my_ds, src);
	
	j = -1;
	for (i = 0; i < 48; ++i)
		if (src[i] == ' ') {
			src[i] = 0;
			j = 0;
		} else {
			if (j == 0 && src[i] <= ' ') continue;
			dst[j++] = src[i];
		}
	if (j == -1) j = 0;
	dst[j] = 0;
	
	f_src = fopen(src, "r");
	if (f_src < 0) {
		puts_no_new_line("error while opening \"");
		puts_no_new_line(src);
		puts("\"");
		exit(0);
	}
	f_dst = fopen(dst, "w");
	if (f_dst < 0) {
		puts_no_new_line("error while opening \"");
		puts_no_new_line(dst);
		puts("\"");
		fclose(f_src);
		exit(0);
	}
	puts_no_new_line("copying file from \"");
	puts_no_new_line(src);
	puts_no_new_line("\" to \"");
	puts_no_new_line(dst);
	puts_no_new_line("\" ...");
	while (fgetbyte(f_src, &w) >= 0) {
		fputbyte(f_dst, w);
	}
	puts("OK");
	fclose(f_src);
	fclose(f_dst);
	exit(0);
}