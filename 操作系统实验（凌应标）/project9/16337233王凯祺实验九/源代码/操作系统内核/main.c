#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "pcb.h"
#include "sleepq.h"

char cmd[256];
char st[20];
int cs9, ip9;
unsigned char zhumian, citou, qishishanqu;
struct PCB PCBlist[64], new_pcb;

struct SleepQueue sleepqueue[64];
int sleepqueue_top;

int signalav[64];
int signal[64];
int signalqueue_top[64];
int signalqueue[64][64];

int now_process;
int ax_save, bx_save, cx_save, dx_save, si_save, di_save, bp_save, es_save, ds_save, ss_save, sp_save, ip_save, cs_save, flags_save;

void welcome() {
	puts("");
	puts("AfricamonkeyOS v9.0.0 built-in shell");
	puts("Enter 'help' for a list of built-in commands.");
	puts("");
}

void help() {
	puts("Built-in commands:");
	puts("------------------");
	puts("exit help kill reboot top");
	puts("");
}

void calc_disk(int id) {
	id = id - 1;
	zhumian = id / 18;
	citou = zhumian % 2;
	zhumian = zhumian / 2;
	qishishanqu = id % 18 + 1;
}

void read_disk(int id, unsigned char size, int memSeg, int memAddr) {
	calc_disk(id);
	
	asm push es
	asm mov ax, memSeg
	asm mov es, ax
	asm mov bx, memAddr
	asm mov cl, qishishanqu
	
	asm mov ah, 2
	asm mov al, size
	asm mov dl, 0
	asm mov dh, citou
	asm mov ch, zhumian
	
	asm int 13h
	asm pop es
}

int search_file(const char *name, const char *extname) {
	int i, j, offset, fin, ok;
	unsigned char st[32], tmp;
	for (i = 0; i < 224; ++i) {
		for (j = 0; j < 12; ++j) {
			offset = 0x2600 + i * 0x20 + j;
			asm mov bx, offset
			asm push ds
			asm mov ax, 2000h                /* FAT table */
			asm mov ds, ax
			asm mov al, [bx]
			asm pop ds
			asm mov tmp, al
			st[j] = tmp;
		}
		if (st[0] == 0x00) continue; /* Empty  entry */
		if (st[0] == 0xe5) continue; /* Erased entry */
		fin = 0;
		ok = 1;
		for (j = 0; j < 8; ++j) {
			char c1 = fin ? 0x20 : name[j];
			char c2 = st[j];
			if (c1 == 0x00) {
				c1 = 0x20;
				fin = 1;
			}
			if (c1 >= 'a' && c1 <= 'z') c1 += 'A' - 'a';
			if (c2 >= 'a' && c2 <= 'z') c2 += 'A' - 'a';
			if (c1 != c2) {
				ok = 0;
				break;
			}
		}
		if (!ok) continue;
		fin = 0;
		for (j = 0; j < 3; ++j) {
			char c1 = fin ? 0x20 : extname[j];
			char c2 = st[j + 8];
			if (c1 == 0x00) {
				c1 = 0x20;
				fin = 1;
			}
			if (c1 >= 'a' && c1 <= 'z') c1 += 'A' - 'a';
			if (c2 >= 'a' && c2 <= 'z') c2 += 'A' - 'a';
			if (c1 != c2) {
				ok = 0;
				break;
			}
		}
		if (!ok) continue;
		return 0x2600 + i * 0x20;
	}
	return 0;
}

int get_size(int offset) {
	int i;
	unsigned int t1, t2;
	unsigned char st[4], tmp;
	offset += 0x1c;
	for (i = 0; i < 4; ++i) {
		asm mov bx, offset
		asm push ds
		asm mov ax, 2000h                /* FAT table */
		asm mov ds, ax
		asm mov al, [bx]
		asm pop ds
		asm mov tmp, al
		st[i] = tmp;
		++ offset;
	}
	if (st[2] || st[3]) return 32767;
	t1 = st[0];
	t2 = st[1];
	t1 = t2 << 8 | t1;
	if (t1 > 32767) return 32767;
	return t1;
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
	new_pcb.status = DEAD;
	new_pcb.son_cnt = 0;
	new_pcb.father_pid = 0;
}

void make_alive(int now) {
	PCBlist[now].status = READY;
}

void make_die(int now) {
	PCBlist[now].status = DEAD;
}

void PCBcopy(struct PCB *dst, const struct PCB *src) {
	dst->ax = src->ax;
	dst->bx = src->bx;
	dst->cx = src->cx;
	dst->dx = src->dx;
	dst->si = src->si;
	dst->di = src->di;
	dst->bp = src->bp;
	dst->es = src->es;
	dst->ds = src->ds;
	dst->ss = src->ss;
	dst->sp = src->sp;
	dst->ip = src->ip;
	dst->cs = src->cs;
	dst->flags = src->flags;
}

void save() {
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
	PCBcopy(&PCBlist[now_process], &new_pcb);
	if (PCBlist[now_process].status == RUNNING)
		PCBlist[now_process].status = READY;
	now_process = (now_process + 1) % 64;
	while (PCBlist[now_process].status != READY)
		now_process = (now_process + 1) % 64;
	PCBlist[now_process].status = RUNNING;
	restore(now_process);
}

int next_cluster(int current_cluster) {
	int offset, ret;
	unsigned char a, b;
	offset = 0x200 + current_cluster * 3 / 2;
	asm mov bx, offset
	asm push ds
	asm mov ax, 2000h                /* FAT table */
	asm mov ds, ax
	asm mov al, [bx]
	asm inc bx
	asm mov ah, [bx]
	asm pop ds
	asm mov a, al
	asm mov b, ah
	if (current_cluster & 1) {
		ret = (a >> 4) | ((int)b << 4);
	} else {
		ret = a | (((int)b & 15) << 8);
	}
	return ret;
}

void execute(int first_block, int memSeg, int memAddr) {
	unsigned int t;
	first_block += 0x1a;
	asm mov bx, first_block
	asm push ds
	asm mov ax, 2000h                /* FAT table */
	asm mov ds, ax
	asm mov al, [bx]
	asm inc bx
	asm mov ah, [bx]
	asm pop ds
	asm mov t, ax
	for (; t < 0xff8; t = next_cluster(t)) {
		read_disk(t + 32, 1, memSeg, memAddr);
		memAddr += 0x200;
	}
}

int find_dead_process() {
	int i;
	for (i = 0; i < 64; ++i)
		if (PCBlist[i].status == DEAD)
			return i;
	return -1;
}

int create_new_process(int cs1, int ip1, int first_block, char tmp, const char *pname) {
	int	k;
	asm cli
	if (tmp == -1) return -1;
	clear_new_pcb();
	PCBlist[0].son_cnt += 1;
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
	PCBcopy(&PCBlist[tmp], &new_pcb);
	for (k = 0; pname[k]; ++k)
		PCBlist[tmp].pname[k] = pname[k];
	PCBlist[tmp].pname[k] = 0;
	execute(first_block, cs1, ip1);
	make_alive(tmp);
	asm sti
	asm exe_go:
	asm mov ax, 0a00h
	asm mov ds, ax
	asm mov es, ax
	if (now_process == 0) return 1;
	asm pop ax
	asm mov tmp, al
	PCBlist[0].son_cnt -= 1;
	make_die(tmp);
	asm jmp $
}

int find_exe() {
	char tmp;
	int size;
	int cs1, ip1, ok, offset;

	offset = search_file(cmd, "COM") + search_file(cmd, "EXE");
	if (offset) {
		if (get_size(offset) > 0xe * 0x200) {
			puts("Cannot create process: COM too large");
			return 1;
		}
		asm cli
		tmp = find_dead_process();
		asm sti
		if (tmp == -1) {
			puts("Cannot create process: No available PCB");
			return 1;
		}
		cs1 = 0x3000 + 0x200 * tmp;
		ip1 = 0x100;
		ok = create_new_process(cs1, ip1, offset, tmp, cmd);
		if (ok == -1) {
			puts("Cannot create process.");
			return 1;
		}
		return 1;
	}
	return 0;
}

void create_kernel_process() {
	int i;
	for (i = 0; i < 64; ++i) {
		PCBlist[i].status = DEAD;
		PCBlist[i].father_pid = 0;
	}
	PCBlist[0].father_pid = -1;
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
	puts("=============================================================");
	puts(" PID  | Process Name    | Status    | Father PID | Son Count ");
	puts("------+-----------------+-----------+------------+-----------");
	for (i = 0; i < 64; ++i)
		if (PCBlist[i].status != DEAD) {
			putchar(' ');
			printint_format(i, 5);
			puts_no_new_line("| ");
			puts_format(PCBlist[i].pname, 16);
			puts_no_new_line("| ");
			if (PCBlist[i].status == RUNNING)
				puts_format("RUNNING", 10);
			else if (PCBlist[i].status == READY)
				puts_format("READY", 10);
			else if (PCBlist[i].status == BLOCK)
				puts_format("BLOCK", 10);
			puts_no_new_line("| ");
			if (PCBlist[i].father_pid == -1) puts_format("-", 11);
			else printint_format(PCBlist[i].father_pid, 11);
			puts_no_new_line("| ");
			printint_format(PCBlist[i].son_cnt, 10);
			puts("");
		}
	puts("=============================================================");
}

void kill_pid(int pid, int ret_val) {
	int j;
	if (pid == 0) return;
	if (PCBlist[pid].status == DEAD) return;
	if (ret_val == -2) puts_no_new_line("+ ");
	puts_no_new_line("Process ");
	printint_format(pid, 0);
	puts(" killed");
	PCBlist[pid].status = DEAD;
	PCBlist[PCBlist[pid].father_pid].son_cnt -= 1;
	if (PCBlist[PCBlist[pid].father_pid].son_cnt == 0 &&
		PCBlist[PCBlist[pid].father_pid].status == BLOCK) {
		PCBlist[PCBlist[pid].father_pid].status = READY;
		PCBlist[PCBlist[pid].father_pid].ax = ret_val;
	}
	PCBlist[PCBlist[pid].father_pid].ret_val = ret_val;
	for (j = 0; j < 64; ++j)
		if (PCBlist[j].status != DEAD && PCBlist[j].father_pid == pid) {
			PCBlist[j].father_pid = 0;
			PCBlist[pid].son_cnt -= 1;
			PCBlist[0].son_cnt += 1;
			kill_pid(j, -2);
		}
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
			if (PCBlist[pid].status == DEAD) {
				puts("Process not found");
				return;
			}
			kill_pid(pid, -1);
					
			return;
		} else
		if (cmd[i] >= 33) {
			puts("Usage: kill PID");
			return;
		}
	puts("Usage: kill PID");
}

void main(){
	int i;
	sleepqueue_top = 0;
	for (i = 0; i < 64; ++i)
		signalav[i] = signalqueue_top[i] = 0;
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
			asm cli
			for (i = 0; i < 64; ++i)
				PCBlist[i].status = DEAD;
			return;
		} else
		if (prefix_match(cmd, "top")) {
			asm cli
			print_top();
			asm sti
		} else
		if (prefix_match(cmd, "kill")) {
			asm cli
			kill_process();
			asm sti
		} else
		if (prefix_match(cmd, "reboot")) {
			asm int 19h
		} else
		if (find_exe()) {
			
		} else {
			puts("command not found");
		}
	}
}

void timeint() {
	int i, j;
	save();
	for (i = 0; i < sleepqueue_top; ++i) {
		sleepqueue[i].sleeptime -= 1;
		if (sleepqueue[i].sleeptime <= 0 && PCBlist[sleepqueue[i].val].status == BLOCK) {
			PCBlist[sleepqueue[i].val].status = READY;
			for (j = i; j + 1 < sleepqueue_top; ++j) {
				sleepqueue[j].val = sleepqueue[j + 1].val;
				sleepqueue[j].sleeptime = sleepqueue[j + 1].sleeptime;
			}
			-- i;
			-- sleepqueue_top;
		}
	}
	exchange();
}

void putchar_kernel(char c) {
	char x, y;
	int pos;
	
	if (c == 8) {
		asm mov ah, 03h
		asm mov bx, 0
		asm int 10h
		asm mov x, dh
		asm mov y, dl
		
		pos = x * 80 + y - 1;
		if (pos < 0) pos = 0;
		x = pos / 80;
		y = pos % 80;
		
		asm mov ah, 02h
		asm mov bh, 0
		asm mov dh, x
		asm mov dl, y
		asm int 10h
		
		asm mov ah, 0ah
		asm mov al, 32
		asm mov bh, 0
		asm mov cx, 1
		asm int 10h
		return;
	}
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

void dosint() {
	char tah, tal, tbh, tbl, tch, tcl, tdh, tdl;
	int tax, tbx, tcx, tdx;
	asm mov tdh, dh
	asm mov tdl, dl
	asm mov tdx, dx
	asm mov tch, ch
	asm mov tcl, cl
	asm mov tcx, cx
	asm mov tbh, bh
	asm mov tbl, bl
	asm mov tbx, bx
	asm mov tah, ah
	asm mov tal, al
	asm mov tax, ax
	if (tah == 0x02) {
		putchar_kernel(tdl);
	} else
	if (tah == 0x4c) {
		asm cli
		kill_pid(now_process, tal);
		asm sti
		asm jmp $
	}
}

void StackCopy(int dst_ss, int src_ss) {
	int i;
	asm push ds
	for (i = 0; i < 0x100; i += 0x2) {
		asm mov ax, src_ss
		asm mov ds, ax
		asm mov bx, i
		asm mov dx, [bx]
		asm mov ax, dst_ss
		asm mov ds, ax
		asm mov bx, i
		asm mov [bx], dx
	}
	asm mov ax, dst_ss
	asm mov ds, ax
	asm mov bx, 100h - 2h
	asm mov ax, dst_ss
	asm mov [bx], ax
	asm pop ds
}

void forkint() {
	int tmp;
	save();
	tmp = find_dead_process();
	if (tmp == -1) {
		new_pcb.ax = -1;
		PCBcopy(&PCBlist[now_process], &new_pcb);
	} else {
		StackCopy(0x3000 + 0x200 * tmp, 0x3000 + 0x200 * now_process);
		new_pcb.ax = tmp;
		PCBcopy(&PCBlist[now_process], &new_pcb);
		PCBlist[now_process].son_cnt += 1;
		new_pcb.ax = 0;
		/* new_pcb.cs += (tmp - now_process) * 0x200; */
		/* new_pcb.ds += (tmp - now_process) * 0x200; */
		/* new_pcb.es += (tmp - now_process) * 0x200; */
		new_pcb.ss += (tmp - now_process) * 0x200;
		PCBcopy(&PCBlist[tmp], &new_pcb);
		PCBlist[tmp].father_pid = now_process;
		make_alive(tmp);
	}
	restore(now_process);
}

void waitint() {
	save();
	if (PCBlist[now_process].son_cnt > 0)
		PCBlist[now_process].status = BLOCK;
	else
		new_pcb.ax = PCBlist[now_process].ret_val;
	exchange();
}

void sleepint() {
	int sleeptime;
	save();
	sleeptime = new_pcb.ax;
	if (sleeptime > 0) {
		PCBlist[now_process].status = BLOCK;
		sleepqueue[sleepqueue_top].val = now_process;
		sleepqueue[sleepqueue_top].sleeptime = sleeptime;
		++ sleepqueue_top;
	}
	exchange();
}

void signalint() {
	int p, d, i, ok;
	save();
	p = new_pcb.ax >> 8;
	d = new_pcb.dx;
	if (p == 0x0) {
		ok = -1;
		if (d > 0) {
			for (i = 0; i < 64; ++i)
				if (signalav[i] == 0) {
					signalav[i] = 1;
					signal[i] = d;
					ok = i;
					break;
				}
		}
		new_pcb.ax = ok;
	} else
	if (p == 0x1) {
		if (d >= 0 && d < 64 && signalav[d]) {
			-- signal[d];
			if (signal[d] < 0) {
				signalqueue[d][ signalqueue_top[d]++ ] = now_process;
				PCBlist[now_process].status = BLOCK;
			}
		}
	} else
	if (p == 0x2) {
		if (d >= 0 && d < 64 && signalav[d]) {
			++ signal[d];
			if (signal[d] <= 0 && PCBlist[ signalqueue[d][0] ].status == BLOCK) {
				PCBlist[ signalqueue[d][0] ].status = READY;
				for (i = 0; i + 1 < signalqueue_top[d]; ++i)
					signalqueue[d][i] = signalqueue[d][i + 1];
				-- signalqueue_top[d];
			}
		}
	} else
	if (p == 0x3) {
		if (d >= 0 && d < 64 && signalav[d]) {
			signalav[d] = 0;
		}
	}
	exchange();
}