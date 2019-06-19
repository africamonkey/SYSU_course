#include "stdlib.h"
#include "stdio.h"
#include "stdcon.h"

void lsmain() {
	int i, j, k, offset;
	unsigned int t1, t2;
	unsigned char st[32], tmp;
	puts("");
	puts("+--------+---+------+-------------------+------+----+");
	puts("|FileName|Ext| Attr |   Last Modified   | Size |F.C.|");
	puts("+--------+---+------+-------------------+------+----+");
	for (i = 0; i < 224; ++i) {
		for (j = 0; j < 0x20; ++j) {
			offset = 0x2600 + i * 0x20 + j;
			asm mov bx, offset
			asm push ds
			asm mov ax, FAT_IN_MEMORY_SEG                /* FAT table */
			asm mov ds, ax
			asm mov al, [bx]
			asm pop ds
			asm mov tmp, al
			st[j] = tmp;
		}
		if (st[0] == 0x00) continue; /* Empty  entry */
		if (st[0] == 0xe5) continue; /* Erased entry */
		if (st[0] == 0xff) continue;
		putchar('|');
		for (j = 0; j < 8; ++j) putchar(st[j]);
		putchar('|');
		for (j = 8; j < 11; ++j) putchar(st[j]);
		putchar('|');
		tmp = st[11];
		k = 0;
		if (tmp & 0x01) putchar('R'), ++k;
		if (tmp & 0x02) putchar('H'), ++k;
		if (tmp & 0x04) putchar('S'), ++k;
		if (tmp & 0x08) putchar('V'), ++k;
		if (tmp & 0x10) putchar('D'), ++k;
		if (tmp & 0x20) putchar('A'), ++k;
		for (j = k; j < 6; ++j) putchar(' ');
		putchar('|');
		t1 = st[0x18];
		t2 = st[0x19];
		t1 = t2 << 8 | t1;
		t2 = t1 & 511;
		t1 >>= 9;
		t1 += 1980;
		printint_zero_format(t1, 4);
		putchar('-');
		t1 = t2 >> 5;
		t2 &= 31;
		printint_zero_format(t1, 2);
		putchar('-');
		printint_zero_format(t2, 2);
		putchar(' ');
		t1 = st[0x16];
		t2 = st[0x17];
		t1 = t2 << 8 | t1;
		t2 = t1 & 2047;
		t1 >>= 11;
		printint_zero_format(t1, 2);
		putchar(':');
		t1 = t2 >> 5;
		t2 &= 31;
		printint_zero_format(t1, 2);
		putchar(':');
		t2 *= 2;
		printint_zero_format(t2, 2);
		putchar('|');
		t1 = st[0x1e];
		t2 = st[0x1f];
		if (t1 || t2) {
			puts_no_new_line("65535+");
		} else {
			t1 = st[0x1c];
			t2 = st[0x1d];
			t1 = t2 << 8 | t1;
			printint_format(t1, 6);
		}
		putchar('|');
		t1 = st[0x1a];
		t2 = st[0x1b];
		t1 = t2 << 8 | t1;
		printint_format(t1, 4);
		putchar('|');
		puts("");
	}
	puts("+--------+---+------+-------------------+------+----+");
}