#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char cmd[256];
char st[20];
int cs9, ip9;
unsigned char zhumian, citou, qishishanqu;

void welcome() {
	puts("");
	puts("AfricamonkeyOS v4.0.0 built-in shell");
	puts("Enter 'help' for a list of built-in commands.");
	puts("");
}

void load_int_2(int diskAddr, int memSeg, int memAddr, int intVec) {
	int oldintVec;
	unsigned char id;
	id = diskAddr;
	id = id - 1;
	zhumian = id / 18;
	citou = zhumian % 2;
	zhumian = zhumian / 2;
	qishishanqu = id % 18 + 1;
	
	oldintVec = intVec;
	asm push es
	asm mov ax, memSeg
	asm mov es, ax
	asm mov bx, memAddr
	asm mov cl, qishishanqu
	asm mov ah, 2
	asm mov al, 1
	asm mov dl, 0
	asm mov dh, citou
	asm mov ch, zhumian
	asm int 13h
	asm pop es
	
	asm push ds
	asm mov ax, 0h
	asm mov ds, ax
	intVec = intVec * 4;
	asm mov bx, intVec
	if (oldintVec == 9) {
		asm mov ax, [bx]
		asm mov ip9, ax
	}
	asm mov ax, memAddr
	asm mov [bx], ax
	
	intVec = intVec + 2;
	asm mov bx, intVec
	if (oldintVec == 9) {
		asm mov ax, [bx]
		asm mov cs9, ax
	}
	asm mov ax, 0
	asm mov [bx], ax
	asm pop ds
}

void restore_int(int intVec) {
	asm push ds
	asm mov ax, 0h
	asm mov ds, ax
	if (intVec == 9) {
		intVec = intVec * 4;
		asm mov bx, intVec
		asm mov ax, ip9
		asm mov [bx], ax
		intVec = intVec + 2;
		asm mov bx, intVec
		asm mov ax, cs9
		asm mov [bx], ax
	}
	asm pop ds
}

void load_int() {
	load_int_2(16, 0x0, 0x9500, 8);
	load_int_2(19, 0x0, 0xd100, 0x34);
	load_int_2(20, 0x0, 0xd500, 0x35);
	load_int_2(21, 0x0, 0xd900, 0x36);
	load_int_2(22, 0x0, 0xdd00, 0x37);
}

void help() {
	puts("Built-in commands:");
	puts("------------------");
	puts("exit help ls");
	puts("");
}

int get_file_size(int id) {
	char tmp;
	int i = 0, j = 0, addr;
	asm mov bx, 8400h
	asm mov ah, 2
	asm mov al, 1
	asm mov dl, 0
	asm mov dh, 0
	asm mov ch, 0
	asm mov cl, id
	asm int 13h
	asm mov ax, 8400h
	asm mov addr, ax
	for (i = 0; i < 512; ++i) {
		asm mov bx, addr
		asm mov al, [bx]
		asm mov tmp, al
		asm inc bx
		asm mov addr, bx
		if (tmp != 0)
			j = i + 1;
	}
	return j;
}

void ls() {
	char tmp;
	int size, i, j, k, addr;
	
	asm mov bx, 8000h
	asm mov ah, 2
	asm mov al, 1
	asm mov dl, 0
	asm mov dh, 0
	asm mov ch, 0
	asm mov cl, 11
	asm int 13h
	
	asm mov ax, 8000h
	asm mov addr, ax
	puts("===============================");
	puts_format("Filename", 15);
	putchar('|');
	puts_format("Sector", 10);
	putchar('|');
	puts("Size");
	puts("-------------------------------");
	for (i = 0; ; ++i) {
		j = 0;
		asm mov bx, addr
		asm mov al, [bx]
		asm mov tmp, al
		asm inc bx
		asm mov addr, bx
		while (tmp) {
			st[j] = tmp;
			asm mov bx, addr
			asm mov al, [bx]
			asm mov tmp, al
			asm inc bx
			asm mov addr, bx
			++j;
		}
		st[j] = '\000';
		if (j == 0) break;
		asm mov bx, addr
		asm mov al, [bx]
		asm mov tmp, al
		asm inc bx
		asm mov addr, bx
		puts_format(st, 15);
		putchar('|');
		printint_format(tmp, 10);
		putchar('|');
		size = get_file_size(tmp);
		printint(size);
	}
	puts("===============================");
}

void execute(unsigned char id) {
	load_int_2(17, 0x0, 0x9900, 9);
	id = id - 1;
	zhumian = id / 18;
	citou = zhumian % 2;
	zhumian = zhumian / 2;
	qishishanqu = id % 18 + 1;
	id = id + 1;

	asm push es
	asm mov ax, 0h
	asm mov es, ax
	asm mov bx, 9100h
	asm mov cl, qishishanqu
	
	asm mov ah, 2
	asm mov al, 1
	asm mov dl, 0
	asm mov dh, citou
	asm mov ch, zhumian
	asm int 13h
	asm pop es
	
	asm push es
	asm push ds
	asm mov ax, 0h
	asm mov es, ax
	asm mov ax, 9100h
	asm call ax
	asm pop ds
	asm pop es
	restore_int(9);
}

int find_exe() {
	char tmp;
	int size, i, j, k, addr;
	asm mov bx, 8000h
	asm mov ah, 2
	asm mov al, 1
	asm mov dl, 0
	asm mov dh, 0
	asm mov ch, 0
	asm mov cl, 11
	asm int 13h
	
	asm mov ax, 8000h
	asm mov addr, ax
	for (i = 0; ; ++i) {
		j = 0;
		asm mov bx, addr
		asm mov al, [bx]
		asm mov tmp, al
		asm inc bx
		asm mov addr, bx
		while (tmp) {
			st[j] = tmp;
			asm mov bx, addr
			asm mov al, [bx]
			asm mov tmp, al
			asm inc bx
			asm mov addr, bx
			++j;
		}
		st[j] = '\000';
		if (j == 0) break;
		asm mov bx, addr
		asm mov al, [bx]
		asm mov tmp, al
		asm inc bx
		asm mov addr, bx
		if (strcmp(st, cmd) == 0) {
			execute(tmp);
			return 1;
		}
	}
	return 0;
}

main(){
	load_int();
	welcome();
	while (1) {
		puts_no_new_line("$ ");
		gets(cmd);
		if (strcmp(cmd, "") == 0) {
		} else
		if (prefix_match(cmd, "help")) {
			help();
		} else
		if (prefix_match(cmd, "exit")) {
			return;
		} else
		if (prefix_match(cmd, "ls")) {
			ls();
		} else
		if (find_exe()) {
			
		} else {
			puts("command not found");
		}
	}
}

