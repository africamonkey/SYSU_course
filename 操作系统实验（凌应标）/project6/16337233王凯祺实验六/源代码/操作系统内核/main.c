#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "pcb.h"

char cmd[256];
char st[20];
int cs9, ip9;
unsigned char zhumian, citou, qishishanqu;
struct PCB PCBlist[64], new_pcb;
int now_process;
int ax_save, bx_save, cx_save, dx_save, si_save, di_save, bp_save, es_save, ds_save, ss_save, sp_save, ip_save, cs_save, flags_save;

void welcome() {
	puts("");
	puts("AfricamonkeyOS v6.0.0 built-in shell");
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
	/* load_int_2(16+8, 0x0, 0x9500, 8); 8 号中断跳入内核，不再弹球 */
	load_int_2(19+8, 0x0, 0xd100, 0x34);
	load_int_2(20+8, 0x0, 0xd500, 0x35);
	load_int_2(21+8, 0x0, 0xd900, 0x36);
	load_int_2(22+8, 0x0, 0xdd00, 0x37);
}

void help() {
	puts("Built-in commands:");
	puts("------------------");
	puts("exit help kill ls top");
	puts("");
}

int get_file_size(unsigned char id) {
	char tmp;
	int i = 0, j = 0, addr;
	
	id = id - 1;
	zhumian = id / 18;
	citou = zhumian % 2;
	zhumian = zhumian / 2;
	qishishanqu = id % 18 + 1;
	id = id + 1;

	asm push es
	asm mov ax, 0
	asm mov es, ax
	asm mov bx, 8400h
	asm mov cl, qishishanqu
	
	asm mov ah, 2
	asm mov al, 1
	asm mov dl, 0
	asm mov dh, citou
	asm mov ch, zhumian
	
	asm int 13h
	asm pop es
	asm mov ax, 8400h
	asm mov addr, ax
	for (i = 0; i < 512; ++i) {
		asm mov bx, addr
		
		asm push ds
		asm mov ax, 0
		asm mov ds, ax
		asm mov al, [bx]
		asm pop ds
		
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
	asm mov dh, 1
	asm mov ch, 0
	asm mov cl, 1
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

void clear_new_pcb() {
	new_pcb.ax = 0;
	new_pcb.bx = 0;
	new_pcb.cx = 0;
	new_pcb.dx = 0;
	new_pcb.si = 0;
	new_pcb.di = 0;
	new_pcb.bp = 0;
	new_pcb.es = 0;
	new_pcb.ds = 0;
	new_pcb.ss = 0;
	new_pcb.sp = 0;
	new_pcb.ip = 0;
	new_pcb.cs = 0;
	new_pcb.flags = 0;
	new_pcb.alive = 0;
}

void make_alive(int now) {
	PCBlist[now].alive = 1;
}

void make_die(int now) {
	PCBlist[now].alive = 0;
}

void save(int now) {
	int k;
	PCBlist[now].ax = new_pcb.ax;
	PCBlist[now].bx = new_pcb.bx;
	PCBlist[now].cx = new_pcb.cx;
	PCBlist[now].dx = new_pcb.dx;
	PCBlist[now].si = new_pcb.si;
	PCBlist[now].di = new_pcb.di;
	PCBlist[now].bp = new_pcb.bp;
	PCBlist[now].es = new_pcb.es;
	PCBlist[now].ds = new_pcb.ds;
	PCBlist[now].ss = new_pcb.ss;
	PCBlist[now].sp = new_pcb.sp;
	PCBlist[now].ip = new_pcb.ip;
	PCBlist[now].cs = new_pcb.cs;
	PCBlist[now].flags = new_pcb.flags;
}

void restore(int now) {
	ax_save = PCBlist[now].ax;
	bx_save = PCBlist[now].bx;
	cx_save = PCBlist[now].cx;
	dx_save = PCBlist[now].dx;
	si_save = PCBlist[now].si;
	di_save = PCBlist[now].di;
	bp_save = PCBlist[now].bp;
	es_save = PCBlist[now].es;
	ds_save = PCBlist[now].ds;
	ss_save = PCBlist[now].ss;
	sp_save = PCBlist[now].sp;
	ip_save = PCBlist[now].ip;
	cs_save = PCBlist[now].cs;
	flags_save = PCBlist[now].flags;
}

void exchange() {
	save(now_process);
	now_process = (now_process + 1) % 64;
	while (!PCBlist[now_process].alive)
		now_process = (now_process + 1) % 64;
	restore(now_process);
}

void execute(unsigned char id, int memSeg, int memAddr) {
	/* load_int_2(17+8, 0x0, 0x9900, 9); 不再响应 9 号中断 */
	id = id - 1;
	zhumian = id / 18;
	citou = zhumian % 2;
	zhumian = zhumian / 2;
	qishishanqu = id % 18 + 1;
	id = id + 1;

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
	
	/*
	asm push es
	asm push ds
	asm mov ax, memSeg
	asm mov es, ax
	asm mov ax, memAddr
	asm call ax
	asm pop ds
	asm pop es
	*/
	/* restore_int(9); */
}

int find_exe() {
	char tmp;
	int size, i, j, k, addr;
	int cs1, ip1;
	asm mov bx, 8000h
	asm mov ah, 2
	asm mov al, 1
	asm mov dl, 0
	asm mov dh, 1
	asm mov ch, 0
	asm mov cl, 1
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
			if (PCBlist[tmp].alive) {
				puts("error: This program is running");
				return 1;
			}
			clear_new_pcb();
			cs1 = 0x2000 + 0x40 * tmp;
			ip1 = 0x100;
			new_pcb.cs = cs1;
			new_pcb.ds = cs1;
			new_pcb.es = cs1;
			new_pcb.ss = cs1;
			new_pcb.ip = ip1;
			new_pcb.sp = ip1 - 6;
			new_pcb.flags = 512;
			
			asm mov cx, ds
			asm push ds
			asm mov ax, cs1
			asm mov ds, ax
			asm mov bx, ip1
			asm sub bx, 2
			asm mov al, tmp
			asm mov ah, 0
			asm mov [bx], ax
			asm sub bx, 2
			asm mov ax, cx
			asm mov [bx], ax
			asm sub bx, 2
			asm mov ax, offset exe_go
			asm mov [bx], ax
			asm pop ds
			save(tmp);
			for (k = 0; k <= j; ++k)
				PCBlist[tmp].pname[k] = st[k];
			make_alive(tmp);
			execute(tmp, cs1, ip1);
			asm exe_go:
			asm mov ax, 0a00h
			asm mov ds, ax
			asm mov es, ax
			if (now_process == 0) return 1;
			asm pop ax
			asm mov tmp, al
			make_die(tmp);
			asm jmp $
			/*
			exchange(0);
			return 1;
			*/
		}
	}
	return 0;
}

void create_kernel_process() {
	int i;
	for (i = 0; i < 64; ++i)
		PCBlist[i].alive = 0;
	now_process = 0;
	make_alive(now_process);
	PCBlist[0].pname[0] = 'k';
	PCBlist[0].pname[1] = 'e';
	PCBlist[0].pname[2] = 'r';
	PCBlist[0].pname[3] = 'n';
	PCBlist[0].pname[4] = 'e';
	PCBlist[0].pname[5] = 'l';
	PCBlist[0].pname[6] = '\000';
}

void print_top() {
	int i, k;
	puts("=============================");
	puts("Process ID | Process Name    ");
	puts("-----------------------------");
	for (i = 0; i < 64; ++i)
		if (PCBlist[i].alive) {
			printint_format(i, 10);
			puts_no_new_line(" | ");
			puts(PCBlist[i].pname);
		}
	puts("=============================");
}

void kill_process() {
	int pid, i, j;
	pid = 0;
	for (i = 4; cmd[i]; ++i)
		if (cmd[i] >= '0' && cmd[i] <= '9') {
			for (j = i; cmd[j] >= '0' && cmd[j] <= '9'; ++j) {
				pid = pid * 10 + cmd[j] - '0';
				if (pid >= 64) {
					puts("Process not found");
					return;
				}
			}
			if (pid == 0) {
				puts("Kernel process can not be killed");
				return;
			}
			if (PCBlist[pid].alive == 0) {
				puts("Process not found");
				return;
			}
			PCBlist[pid].alive = 0;
			puts_no_new_line("Process ");
			printint_format(pid, 0);
			puts(" killed");
			return;
		} else
		if (st[i] >= 33) {
			puts("Usage: kill PID");
			return;
		}
	puts("Usage: kill PID");
}

void main(){
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
		if (prefix_match(cmd, "top")) {
			print_top();
		} else
		if (prefix_match(cmd, "kill")) {
			kill_process();
		} else
		if (find_exe()) {
			
		} else {
			puts("command not found");
		}
	}
}

void timeint() {
	new_pcb.ax = ax_save;
	new_pcb.bx = bx_save;
	new_pcb.cx = cx_save;
	new_pcb.dx = dx_save;
	new_pcb.si = si_save;
	new_pcb.di = di_save;
	new_pcb.bp = bp_save;
	new_pcb.es = es_save;
	new_pcb.ds = ds_save;
	new_pcb.ss = ss_save;
	new_pcb.sp = sp_save;
	new_pcb.ip = ip_save;
	new_pcb.cs = cs_save;
	new_pcb.flags = flags_save;
	new_pcb.alive = 1;
	exchange();
}