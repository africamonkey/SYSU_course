#include "stdlib.h"
#include "stdio.h"
#include "stdcon.h"

void bpbmain() {
	unsigned char st[0x40], tmp;
	int i;
	for (i = 0; i < 0x40; ++i) {
		asm mov bx, i
		asm push ds
		asm mov ax, FAT_IN_MEMORY_SEG                /* FAT table */
		asm mov ds, ax
		asm mov al, [bx]
		asm pop ds
		asm mov tmp, al
		st[i] = tmp;
	}
	puts("--- BPB Info ---");
	puts_no_new_line("OEM Name: ");
	for (i = 0; i < 8; ++i) putchar(st[i + 0x03]);
	puts("");
	puts_no_new_line("Bytes per sector: ");
	i = (int)st[0x0b] + (((int)st[0x0c]) << 8);
	printint(i);
	puts_no_new_line("Sectors per cluster: ");
	printint((int)st[0x0d]);
	puts_no_new_line("Reserved sector count: ");
	i = (int)st[0x0e] + (((int)st[0x0f]) << 8);
	printint(i);
	puts_no_new_line("Number of file allocation tables: ");
	printint((int)st[0x10]);
	puts_no_new_line("Maximum number of root directory: ");
	i = (int)st[0x11] + (((int)st[0x12]) << 8);
	printint(i);
	puts_no_new_line("Total sectors: ");
	i = (int)st[0x13] + (((int)st[0x14]) << 8);
	printint(i);
	puts_no_new_line("Sectors per File Allocation Table: ");
	i = (int)st[0x16] + (((int)st[0x17]) << 8);
	printint(i);
	puts_no_new_line("Sectors per track: ");
	i = (int)st[0x18] + (((int)st[0x19]) << 8);
	printint(i);
	puts_no_new_line("Number of heads: ");
	i = (int)st[0x1a] + (((int)st[0x1b]) << 8);
	printint(i);
	puts_no_new_line("Hidden sectors: ");
	i = (int)st[0x1c] + (((int)st[0x1d]) << 8);
	printint(i);
	puts("");
	puts("--- EBPB Info ---");
	puts_no_new_line("Physical drive number: ");
	printint((int)st[0x24]);
	puts_no_new_line("Extended boot signature: ");
	printhex((int)st[0x26]);
	puts_no_new_line("Volume serial number: ");
	printhex_no_new_line_no_0x(st[0x2a] >> 4);
	printhex_no_new_line_no_0x(st[0x2a] & 15);
	printhex_no_new_line_no_0x(st[0x29] >> 4);
	printhex_no_new_line_no_0x(st[0x29] & 15);
	puts_no_new_line("-");
	printhex_no_new_line_no_0x(st[0x28] >> 4);
	printhex_no_new_line_no_0x(st[0x28] & 15);
	printhex_no_new_line_no_0x(st[0x27] >> 4);
	printhex_no_new_line_no_0x(st[0x27] & 15);
	puts("");
	puts_no_new_line("Volume label: ");
	for (i = 0; i < 11; ++i) putchar(st[i + 0x2B]);
	puts("");
	puts_no_new_line("File-system type: ");
	for (i = 0; i < 8; ++i) putchar(st[i + 0x36]);
	puts("");
}