#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "pcb.h"
#include "sleepq.h"
#include "ftable.h"
#include "sync.h"
#include "stdcon.h"

char cmd[256];
char st[20];
int cs9, ip9;
unsigned char zhumian, citou, qishishanqu;
struct PCB PCBlist[MAX_PROCESS_NUM], new_pcb;

struct SleepQueue sleepqueue[MAX_PROCESS_NUM];
int sleepqueue_top;

int signalav[MAX_SIGNAL_NUM];
int signal[MAX_SIGNAL_NUM];
int signalqueue_top[MAX_SIGNAL_NUM];
int signalqueue[MAX_SIGNAL_NUM][MAX_PROCESS_NUM];

struct processFileTable proFT[MAX_PROCESS_NUM][MAX_FILES_PER_PROCESS];
struct globalFileTable gloFT[MAX_FILES_PER_SYSTEM];
int gloFTsignal;
int fileCacheSignal;
int clusterSignal;
int calcDiskSignal;

int now_process;
int ax_save, bx_save, cx_save, dx_save, si_save, di_save, bp_save, es_save, ds_save, ss_save, sp_save, ip_save, cs_save, flags_save;

void welcome() {
	puts("");
	puts("AfricamonkeyOS v10.0.0 built-in shell");
	puts("Enter 'help' for a list of built-in commands.");
	puts("");
}

void help() {
	puts("Built-in commands:");
	puts("------------------");
	puts("exit help kill reboot top");
	puts("");
}

void print_file_info();

void calc_disk(int id) {
	id = id - 1;
	zhumian = id / 18;
	citou = zhumian % 2;
	zhumian = zhumian / 2;
	qishishanqu = id % 18 + 1;
}

void read_disk(int id, unsigned char size, int memSeg, int memAddr) {
	P(calcDiskSignal);
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
	V(calcDiskSignal);
}

void write_disk(int id, unsigned char size, int memSeg, int memAddr) {
	P(calcDiskSignal);
	calc_disk(id);
	
	asm push es
	asm mov ax, memSeg
	asm mov es, ax
	asm mov bx, memAddr
	asm mov cl, qishishanqu
	
	asm mov ah, 3
	asm mov al, size
	asm mov dl, 0
	asm mov dh, citou
	asm mov ch, zhumian
	
	asm int 13h
	asm pop es
	V(calcDiskSignal);
}

int search_file(int name_ds, const char *name, const char *extname) {
	int i, j, offset, fin, ok;
	char c1, c2;
	unsigned char st[32], tmp;
	for (i = 0; i < 8; ++i) {
		asm push ds
		asm mov ax, name_ds
		asm mov ds, ax
		tmp = name[i];
		asm pop ds
	}
	for (i = 0; i < 3; ++i) {
		asm push ds
		asm mov ax, name_ds
		asm mov ds, ax
		tmp = extname[i];
		asm pop ds
	}
	for (i = 0; i < 224; ++i) {
		for (j = 0; j < 12; ++j) {
			offset = 0x2600 + i * 0x20 + j;
			P(clusterSignal);
			asm mov bx, offset
			asm push ds
			asm mov ax, FAT_IN_MEMORY_SEG                /* FAT table */
			asm mov ds, ax
			asm mov al, [bx]
			asm pop ds
			asm mov tmp, al
			V(clusterSignal);
			st[j] = tmp;
		}
		if (st[0] == 0x00) continue; /* Empty  entry */
		if (st[0] == 0xe5) continue; /* Erased entry */
		if (st[0] == 0xff) continue;
		fin = 0;
		ok = 1;
		for (j = 0; j < 8; ++j) {
			asm push ds
			asm mov ax, name_ds
			asm mov ds, ax
			c1 = fin ? 0x20 : name[j];
			asm pop ds
			c2 = st[j];
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
			asm push ds
			asm mov ax, name_ds
			asm mov ds, ax
			c1 = fin ? 0x20 : extname[j];
			asm pop ds
			c2 = st[j + 8];
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
	P(clusterSignal);
	offset += 0x1c;
	for (i = 0; i < 4; ++i) {
		asm mov bx, offset
		asm push ds
		asm mov ax, FAT_IN_MEMORY_SEG                /* FAT table */
		asm mov ds, ax
		asm mov al, [bx]
		asm pop ds
		asm mov tmp, al
		st[i] = tmp;
		++ offset;
	}
	if (st[2] || st[3]) {
		V(clusterSignal);
		return 32765;
	}
	t1 = st[0];
	t2 = st[1];
	t1 = t2 << 8 | t1;
	if (t1 > 32765) {
		V(clusterSignal);
		return 32765;
	}
	V(clusterSignal);
	return t1;
}

void set_size(int offset, int size) {
	P(clusterSignal);
	offset += 0x1c;
	asm mov bx, offset
	asm push ds
	asm mov ax, FAT_IN_MEMORY_SEG                /* FAT table */
	asm mov ds, ax
	asm mov ax, size
	asm mov [bx], ax
	asm pop ds
	V(clusterSignal);
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
	now_process = (now_process + 1) % MAX_PROCESS_NUM;
	while (PCBlist[now_process].status != READY)
		now_process = (now_process + 1) % MAX_PROCESS_NUM;
	PCBlist[now_process].status = RUNNING;
	restore(now_process);
}

void noexchange() {
	PCBcopy(&PCBlist[now_process], &new_pcb);
	restore(now_process);
}

int first_cluster(int offset) {
	int t;
	P(clusterSignal);
	offset += 0x1a;
	asm mov bx, offset
	asm push ds
	asm mov ax, FAT_IN_MEMORY_SEG                /* FAT table */
	asm mov ds, ax
	asm mov al, [bx]
	asm inc bx
	asm mov ah, [bx]
	asm pop ds
	asm mov t, ax
	V(clusterSignal);
	return t;
}

int next_cluster_without_pv(int current_cluster) {
	int offset, ret;
	unsigned char a, b;
	offset = 0x200 + current_cluster * 3 / 2;
	asm mov bx, offset
	asm push ds
	asm mov ax, FAT_IN_MEMORY_SEG                /* FAT table */
	asm mov ds, ax
	asm mov al, [bx]
	asm inc bx
	asm mov ah, [bx]
	asm pop ds
	asm mov a, al
	asm mov b, ah
	if (current_cluster & 1) {
		ret = (((int)a) >> 4) | (((int)b) << 4);
	} else {
		ret = ((int)a) | (((int)b & 15) << 8);
	}
	return ret;
}

int next_cluster(int current_cluster) {
	int ret;
	P(clusterSignal);
	ret = next_cluster_without_pv(current_cluster);
	V(clusterSignal);
	return ret;
}

void _modify_cluster_without_pv(int current_cluster, int val, int offset) {
	unsigned char a, b;
	asm mov bx, offset
	asm push ds
	asm mov ax, FAT_IN_MEMORY_SEG
	asm mov ds, ax
	asm mov al, [bx]
	asm inc bx
	asm mov ah, [bx]
	asm pop ds
	asm mov a, al
	asm mov b, ah
	if (current_cluster & 1) {
		a = ((int)a & 0x0f) | ((val & 0x0f) << 4);
		b = val >> 4;
	} else {
		a = val & 0xff;
		b = ((int)b & 0xf0) | (val >> 8);
	}
	asm mov bx, offset
	asm push ds
	asm mov ax, FAT_IN_MEMORY_SEG
	asm mov ds, ax
	asm mov al, a
	asm mov ah, b
	asm mov [bx], al
	asm inc bx
	asm mov [bx], ah
	asm pop ds
}

void modify_cluster_without_pv(int current_cluster, int val) {
	_modify_cluster_without_pv(current_cluster, val, 0x200 + current_cluster * 3 / 2);
	_modify_cluster_without_pv(current_cluster, val, 0x1400 + current_cluster * 3 / 2);
}

void modify_cluster(int current_cluster, int val) {
	P(clusterSignal);
	modify_cluster_without_pv(current_cluster, val);
	V(clusterSignal);
}

int available_cluster(int current_cluster) {
	int i;
	P(clusterSignal);
	for (i = 2; i < 2833; ++i)
		if (next_cluster_without_pv(i) == 0x000) {
			if (current_cluster) modify_cluster_without_pv(current_cluster, i);
			modify_cluster_without_pv(i, 0xfff);
			V(clusterSignal);
			return i;
		}
	V(clusterSignal);
	return -1;
}

int add_file_description(int now_ds, const char *a, const char *b, int first_cluster) {
	int i, j, offset;
	unsigned char tmp;
	P(clusterSignal);
	for (i = 0; i < 224; ++i) {
		offset = 0x2600 + i * 0x20;
		asm mov bx, offset
		asm push ds
		asm mov ax, FAT_IN_MEMORY_SEG                /* FAT table */
		asm mov ds, ax
		asm mov al, [bx]
		asm pop ds
		asm mov tmp, al
		if (tmp == 0x00 || tmp == 0xe5) {
			for (j = 0; j < 0x20; ++j) {
				offset = 0x2600 + i * 0x20 + j;
				asm mov bx, offset
				asm push ds
				asm mov ax, FAT_IN_MEMORY_SEG
				asm mov ds, ax
				asm mov al, 0h
				asm mov [bx], al
				asm pop ds
			}
			for (j = 0; j < 8; ++j) {
				offset = 0x2600 + i * 0x20 + j;
				asm push ds
				asm mov ax, now_ds
				asm mov ds, ax
				tmp = a[j];
				asm pop ds
				if (tmp >= 'a' && tmp <= 'z') tmp += 'A' - 'a';
				asm mov bx, offset
				asm push ds
				asm mov ax, FAT_IN_MEMORY_SEG
				asm mov ds, ax
				asm mov al, tmp
				asm mov [bx], al
				asm pop ds
			}
			for (j = 0; j < 3; ++j) {
				offset = 0x2600 + i * 0x20 + j + 8;
				asm push ds
				asm mov ax, now_ds
				asm mov ds, ax
				tmp = b[j];
				asm pop ds
				if (tmp >= 'a' && tmp <= 'z') tmp += 'A' - 'a';
				asm mov bx, offset
				asm push ds
				asm mov ax, FAT_IN_MEMORY_SEG
				asm mov ds, ax
				asm mov al, tmp
				asm mov [bx], al
				asm pop ds
			}
			offset = 0x2600 + i * 0x20 + 0x0b;
			tmp = 0x20;
			asm mov bx, offset
			asm push ds
			asm mov ax, FAT_IN_MEMORY_SEG
			asm mov ds, ax
			asm mov al, tmp
			asm mov [bx], al
			asm pop ds
			
			offset = 0x2600 + i * 0x20 + 0x1a;
			asm mov bx, offset
			asm push ds
			asm mov ax, FAT_IN_MEMORY_SEG
			asm mov ds, ax
			asm mov ax, first_cluster
			asm mov [bx], ax
			asm pop ds

			V(clusterSignal);
			return 0x2600 + i * 0x20;
		}
	}
	V(clusterSignal);
	return -1;
}

void read_FAT_from_disk() {
	P(clusterSignal);
	read_disk(1, 33, FAT_IN_MEMORY_SEG, 0x0);
	V(clusterSignal);
}

void write_FAT_to_disk() {
	P(clusterSignal);
	write_disk(1, 33, FAT_IN_MEMORY_SEG, 0x0);
	V(clusterSignal);
}

void del_file(int offset) {
	unsigned int t, tn;
	t = first_cluster(offset);
	for (; t < 0xff8;) {
		tn = next_cluster(t);
		modify_cluster(t, 0x000);
		t = tn;
	}
	P(clusterSignal);
	asm mov bx, offset
	asm push ds
	asm mov ax, FAT_IN_MEMORY_SEG
	asm mov ds, ax
	asm mov al, 0e5h
	asm mov [bx], al
	asm pop ds
	V(clusterSignal);
	write_FAT_to_disk();
}

int detect_occupy(int first_cluster) {
	int i;
	P(gloFTsignal);
	for (i = 0; i < MAX_FILES_PER_SYSTEM; ++i)
		if (gloFT[i].valid && gloFT[i].first_cluster == first_cluster) {
			if (gloFT[i].method == 'r') {
				V(gloFTsignal);
				return 1;
			}
			if (gloFT[i].method == 'w') {
				V(gloFTsignal);
				return 2;
			}
			V(gloFTsignal);
			return 3;
		}
	V(gloFTsignal);
	return 0;
}


int add_gloFT(char method, int first_cluster) {
	int i;
	P(gloFTsignal);
	for (i = 0; i < MAX_FILES_PER_SYSTEM; ++i)
		if (gloFT[i].valid && gloFT[i].first_cluster == first_cluster) {
			if (gloFT[i].method != method) {
				V(gloFTsignal);
				return -1;
			} else {
				gloFT[i].count += 1;
				V(gloFTsignal);
				return i;
			}
		} else
		if (gloFT[i].valid == 0) {
			gloFT[i].valid = 1;
			gloFT[i].method = method;
			gloFT[i].first_cluster = first_cluster;
			gloFT[i].count = 1;
			V(gloFTsignal);
			return i;
		}
	V(gloFTsignal);
	return -1;
}

unsigned char read_char(int process_id, int f_id) {
	return proFT[process_id][f_id].cache[proFT[process_id][f_id].current_pointer];
}

void write_char(int process_id, int f_id, unsigned char val) {
	proFT[process_id][f_id].cache[proFT[process_id][f_id].current_pointer] = val;
}

void read_file(int process_id, int f_id) {
	unsigned int ds1, ip1;
	asm mov ax, ds
	asm mov ds1, ax
	ip1 = proFT[process_id][f_id].cache;
	read_disk(proFT[process_id][f_id].current_cluster + 32, 1, ds1, ip1);
}

void write_file(int process_id, int f_id) {
	unsigned int ds1, ip1;
	asm mov ax, ds
	asm mov ds1, ax
	ip1 = proFT[process_id][f_id].cache;
	write_disk(proFT[process_id][f_id].current_cluster + 32, 1, ds1, ip1);
} 

int addFileTable(int process_id, char method, int first_cluster, int size, int offset) {
	int i;
	for (i = 0; i < MAX_FILES_PER_PROCESS; ++i)
		if (proFT[process_id][i].valid == 0) {
			if (add_gloFT(method, first_cluster) != -1) {
				proFT[process_id][i].valid = 1;
				proFT[process_id][i].method = method;
				proFT[process_id][i].offset = offset;
				proFT[process_id][i].first_cluster = first_cluster;
				proFT[process_id][i].size = size;
				proFT[process_id][i].current_cluster = first_cluster;
				proFT[process_id][i].current_pointer = 0;
				proFT[process_id][i].current_size = 0;
				read_file(process_id, i);
				return i;
			} else {
				return -1;
			}
		}
	return -1;
}

int del_gloFT(char method, int first_cluster) {
	int i;
	P(gloFTsignal);
	for (i = 0; i < MAX_FILES_PER_SYSTEM; ++i)
		if (gloFT[i].valid && gloFT[i].first_cluster == first_cluster) {
			if (gloFT[i].method != method) {
				V(gloFTsignal);
				return -1;
			} else {
				gloFT[i].count -= 1;
				if (gloFT[i].count == 0)
					gloFT[i].valid = 0;
				V(gloFTsignal);
				return 0;
			}
		}
	V(gloFTsignal);
	return 0;
}

int delFileTable(int process_id, int fid) {
	if (process_id < 0 || process_id >= MAX_PROCESS_NUM) return -1;
	if (fid < 0 || fid >= MAX_FILES_PER_PROCESS) return -1;
	if (proFT[process_id][fid].valid == 0) return -1;
	write_file(process_id, fid);
	del_gloFT(proFT[process_id][fid].method, proFT[process_id][fid].first_cluster);
	if (proFT[process_id][fid].method == 'w') {
		set_size(proFT[process_id][fid].offset, proFT[process_id][fid].current_size);
		write_FAT_to_disk();
	}
	proFT[process_id][fid].valid = 0;
	return 0;
}

/*

Too slow.

unsigned char read_file(int cluster, int pointer) {
	unsigned char w;
	P(fileCacheSignal);
	read_disk(cluster + 32, 1, TEMP_SEG, 0x0);
	asm push ds
	asm mov ax, TEMP_SEG
	asm mov ds, ax
	asm mov bx, pointer
	asm mov al, [bx]
	asm mov w, al
	asm pop ds
	V(fileCacheSignal);
	return w;
}

void write_file(int cluster, int pointer, unsigned char w) {
	P(fileCacheSignal);
	read_disk(cluster + 32, 1, TEMP_SEG, 0x0);
	asm push ds
	asm mov ax, TEMP_SEG
	asm mov ds, ax
	asm mov bx, pointer
	asm mov al, w
	asm mov [bx], al
	asm pop ds
	write_disk(cluster + 32, 1, TEMP_SEG, 0x0);
	V(fileCacheSignal);
}

*/

void execute(int offset, int memSeg, int memAddr) {
	unsigned int t;
	t = first_cluster(offset);
	for (; t < 0xff8; t = next_cluster(t)) {
		read_disk(t + 32, 1, memSeg, memAddr);
		memAddr += 0x200;
	}
}

int find_dead_process() {
	int i;
	for (i = 0; i < MAX_PROCESS_NUM; ++i)
		if (PCBlist[i].status == DEAD)
			return i;
	return -1;
}

int create_new_process(int cs1, int ip1, int first_block, char pid, int name_ds, const char *pname, const char *parameter) {
	int	k;
	char tmp;
	asm cli
	if (pid == -1) return -1;
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
	asm mov al, pid
	asm mov ah, 0
	asm mov [bx], ax
	asm sub bx, 2
	asm mov ax, cx
	asm mov [bx], ax
	asm sub bx, 2
	asm mov ax, offset exe_go
	asm mov [bx], ax
	asm pop ds
	PCBcopy(&PCBlist[pid], &new_pcb);
	for (k = 0; k < MAX_EXENAME_LEN; ++k) {
		asm push ds
		asm mov ax, name_ds
		asm mov ds, ax
		tmp = pname[k];
		asm pop ds
		PCBlist[pid].pname[k] = tmp;
		if (tmp == 0x0) break;
	}
	PCBlist[pid].pname[k] = 0;
	for (k = 0; k < MAX_PARAMETER_LEN; ++k) {
		asm push ds
		asm mov ax, name_ds
		asm mov ds, ax
		tmp = parameter[k];
		asm pop ds
		PCBlist[pid].parameter[k] = tmp;
		if (tmp == 0x0) break;
	}
	PCBlist[pid].parameter[k] = 0;
	execute(first_block, cs1, ip1);
	make_alive(pid);
	asm sti
	asm exe_go:
	asm mov ax, 0a00h
	asm mov ds, ax
	asm mov es, ax
	if (now_process == 0) return 1;
	asm pop ax
	asm mov pid, al
	PCBlist[0].son_cnt -= 1;
	make_die(pid);
	asm jmp $
}

int find_exe() {
	char tmp, pid, exename[MAX_EXENAME_LEN], parameter[MAX_PARAMETER_LEN];
	int size, now_ds;
	int cs1, ip1, ok, offset;
	int i, len, j, k;
	
	len = strlen(cmd);
	cmd[len] = 0;
	j = k = 0;
	exename[0] = parameter[0] = 0;
	for (i = 0; i <= len; ++i) {
		if (j == -1) {
			if (k == 0 && cmd[i] <= ' ') continue;
			tmp = cmd[i];
			asm push ds
			asm mov ax, ss
			asm mov ds, ax
			parameter[k++] = tmp;
			asm pop ds
		} else {
			if (j == 0 && cmd[i] <= ' ') continue;
			tmp = cmd[i];
			asm push ds
			asm mov ax, ss
			asm mov ds, ax
			exename[j++] = tmp;
			asm pop ds
			if (cmd[i] <= ' ') {
				asm push ds
				asm mov ax, ss
				asm mov ds, ax
				exename[j - 1] = 0;
				asm pop ds
				j = -1;
			}
		}
	}
	asm push ds
	asm mov ax, ss
	asm mov ds, ax
	parameter[k] = 0;
	asm pop ds
	
	asm mov ax, ss
	asm mov now_ds, ax
	offset = search_file(now_ds, exename, "COM");
	if (offset == 0) offset = search_file(now_ds, exename, "EXE");
	if (offset) {
		if (get_size(offset) > 0xe * 0x200) {
			puts("Cannot create process: COM too large");
			return 1;
		}
		asm cli
		pid = find_dead_process();
		asm sti
		if (pid == -1) {
			puts("Cannot create process: No available PCB");
			return 1;
		}
		cs1 = USER_PROGRAM_IN_MEMORY_SEG + 0x200 * pid;
		ip1 = 0x100;
		ok = create_new_process(cs1, ip1, offset, pid, now_ds, exename, parameter);
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
	for (i = 0; i < MAX_PROCESS_NUM; ++i) {
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
	PCBlist[0].parameter[0] = '\000';
}

void print_top() {
	int i, k;
	puts("==============================================================================");
	puts(" PID  | Process Name    | Parameter      | Status    | Father PID | Son Count ");
	puts("------+-----------------+----------------+-----------+------------+-----------");
	for (i = 0; i < MAX_PROCESS_NUM; ++i)
		if (PCBlist[i].status != DEAD) {
			putchar(' ');
			printint_format(i, 5);
			puts_no_new_line("| ");
			puts_format(PCBlist[i].pname, 16);
			puts_no_new_line("| ");
			puts_format(PCBlist[i].parameter, 15);
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
	puts("==============================================================================");
}

void print_file_info() {
	int i, j;
	puts("Global File Table");
	puts("===================");
	puts(" M. | F.C. | count ");
	puts("----+------+-------");
	for (i = 0; i < MAX_FILES_PER_SYSTEM; ++i) {
		if (gloFT[i].valid == 0x00) continue;
		putchar(' ');
		putchar(gloFT[i].method);
		puts_no_new_line("  | ");
		printint_format(gloFT[i].first_cluster, 4);
		puts_no_new_line(" | ");
		printint_format(gloFT[i].count, 5);
		puts("");
	}
	puts("===================");
	puts("Process File Table");
	puts("======================================================");
	puts(" PID | M. | offset | F.C. | size | C.C. | C.P. | C.S. ");
	puts("-----+----+--------+------+------+------+------+------");
	for (i = 0; i < MAX_PROCESS_NUM; ++i) {
		for (j = 0; j < MAX_FILES_PER_PROCESS; ++j) {
			if (proFT[i][j].valid == 0x00) continue;
			putchar('  ');
			printint_format(i, 3);
			puts_no_new_line(" | ");
			putchar(proFT[i][j].method);
			puts_no_new_line("  | ");
			printint_format(proFT[i][j].offset, 6);
			puts_no_new_line(" | ");
			printint_format(proFT[i][j].first_cluster, 4);
			puts_no_new_line(" | ");
			printint_format(proFT[i][j].size, 4);
			puts_no_new_line(" | ");
			printint_format(proFT[i][j].current_cluster, 4);
			puts_no_new_line(" | ");
			printint_format(proFT[i][j].current_pointer, 4);
			puts_no_new_line(" | ");
			printint_format(proFT[i][j].current_size, 4);
			puts("");
		}
	}
	puts("======================================================");
}

void kill_pid(int pid, int ret_val) {
	int j;
	if (pid == 0) return;
	if (PCBlist[pid].status == DEAD) return;
	for (j = 0; j < MAX_FILES_PER_PROCESS; ++j)
		delFileTable(pid, j);
	/*
	if (ret_val == -2) puts_no_new_line("+ ");
	puts_no_new_line("Process ");
	printint_format(pid, 0);
	puts(" killed");
	*/
	PCBlist[pid].status = DEAD;
	PCBlist[PCBlist[pid].father_pid].son_cnt -= 1;
	if (PCBlist[PCBlist[pid].father_pid].son_cnt == 0 &&
		PCBlist[PCBlist[pid].father_pid].status == BLOCK) {
		PCBlist[PCBlist[pid].father_pid].status = READY;
		PCBlist[PCBlist[pid].father_pid].ax = ret_val;
	}
	PCBlist[PCBlist[pid].father_pid].ret_val = ret_val;
	for (j = 0; j < MAX_PROCESS_NUM; ++j)
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
				if (pid >= MAX_PROCESS_NUM) {
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
			asm cli
			kill_pid(pid, -1);
			asm sti
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
	for (i = 0; i < MAX_SIGNAL_NUM; ++i)
		signalav[i] = signalqueue_top[i] = 0;
	gloFTsignal = getSem(1);
	fileCacheSignal = getSem(1);
	clusterSignal = getSem(1);
	calcDiskSignal = getSem(1);
	read_FAT_from_disk();
	
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
			for (i = 0; i < MAX_PROCESS_NUM; ++i)
				PCBlist[i].status = DEAD;
			return;
		} else
		if (prefix_match(cmd, "top")) {
			print_top();
		} else
		if (prefix_match(cmd, "file")) {
			print_file_info();
		} else
		if (prefix_match(cmd, "kill")) {
			kill_process();
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
	
	if (c == 10) return;
	
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
	int tax, tbx, tcx, tdx, i;
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
	if (tah == 0x01) {
		/* dx = ds */
		/* bx = ip */
		for (i = 0; i < MAX_PARAMETER_LEN; ++i) {
			tch = PCBlist[now_process].parameter[i];
			if (tch == 0x00) break;
			asm push ds
			asm mov ax, tdx
			asm mov ds, ax
			asm mov bx, tbx
			asm mov al, tch
			asm mov [bx], al
			asm pop ds
			++ tbx;
		}
	} else
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
		StackCopy(USER_PROGRAM_IN_MEMORY_SEG + 0x200 * tmp, USER_PROGRAM_IN_MEMORY_SEG + 0x200 * now_process);
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
	int p, d, i, ok, exc;
	save();
	p = new_pcb.ax >> 8;
	d = new_pcb.dx;
	exc = 0;
	if (p == 0x0) {
		ok = -1;
		if (d > 0) {
			for (i = 0; i < MAX_SIGNAL_NUM; ++i)
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
		if (d >= 0 && d < MAX_SIGNAL_NUM && signalav[d]) {
			-- signal[d];
			if (signal[d] < 0) {
				signalqueue[d][ signalqueue_top[d]++ ] = now_process;
				PCBlist[now_process].status = BLOCK;
				exc = 1;
			}
		}
	} else
	if (p == 0x2) {
		if (d >= 0 && d < MAX_SIGNAL_NUM && signalav[d]) {
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
		if (d >= 0 && d < MAX_SIGNAL_NUM && signalav[d]) {
			signalav[d] = 0;
		}
	}
	if (exc) exchange(); else noexchange();
}

int kernel_fopen(int filename_ds, const char *filename, char w) {
	char a[9], b[4], tmp;
	int i, j, ext, fc, my_ds;
	ext = 0;
	for (i = 0; i < 9; ++i) a[i] = 0x20;
	for (i = 0; i < 4; ++i) b[i] = 0x20;
	j = 0;
	for (i = 0; i < 12; ++i) {
		asm push ds
		asm mov ax, filename_ds
		asm mov ds, ax
		tmp = filename[i];
		asm pop ds
		if (tmp == 0) break;
		if (i < 8 && !ext) {
			if (tmp != '.') {
				a[i] = tmp;
			}
		}
		if (ext) {
			asm push ds
			asm mov ax, ss
			asm mov ds, ax
			b[j] = tmp;
			asm pop ds
			++ j;
			if (j >= 3) break;
		}
		if (tmp == '.') ext = 1;
	}
	asm mov ax, ss
	asm mov my_ds, ax
	ext = search_file(my_ds, a, b);
	if (w == 'r') {
		if (ext == 0) return -1;
		if (detect_occupy(first_cluster(ext)) == 2) return -2;
		return addFileTable(now_process, w, first_cluster(ext), get_size(ext), ext);
	} else
	if (w == 'w') {
		if (ext) {
			if (detect_occupy(first_cluster(ext))) return -2;
			del_file(ext);
		}
		ext = available_cluster(0);
		j = add_file_description(my_ds, a, b, ext);
		if (j == -1) return -3;
		if (ext == -1) return -3;
		modify_cluster(ext, 0xfff);
		write_FAT_to_disk();
		return addFileTable(now_process, w, ext, 0, j);
	} else
	if (w == 'd') {
		if (ext) {
			del_file(ext);
			return 0;
		}
		return -1;
	}
	return -4;
}

int fileint() {
	unsigned int ax1, bx1, cx1, dx1;
	unsigned char ah1, al1;
	int ret_val, ds1;
	char w, filename[13];
	asm mov ax1, ax
	asm mov bx1, bx
	asm mov cx1, cx
	asm mov dx1, dx
	asm mov ah1, ah
	asm mov al1, al
	
	if (ah1 == 0x00) {
		/* fopen */
		/* bx1 = filename* (IP) */
		/* cx1 = type*(IP)      */
		/* dx1 = ds             */
		asm push ds
		asm mov ax, dx1
		asm mov ds, ax
		asm mov bx, cx1
		asm mov al, [bx]
		asm mov w, al
		asm pop ds
		asm mov ax, ss
		asm mov ds1, ax
		strcpy_from_ds_ip(ds1, filename, dx1, bx1);
		ret_val = kernel_fopen(ds1, filename, w);
		if (ret_val >= 0) {
			/* puts("OK"); */
		} else
		if (ret_val == -1) {
			/* puts("File not found"); */
		} else
		if (ret_val == -2) {
			/* puts("File is being occupied by other process"); */
		} else
		if (ret_val == -3) {
			/* puts("No enough space"); */
		} else
		if (ret_val == -4) {
			/* puts("Unknown open method"); */
		} else {
			/* puts("Unknown error"); */
		}
	} else
	if (ah1 == 0x01) {
		/* fgetbyte */
		/* bx1 = f_id           */
		/* cx1 = w*             */
		/* dx1 = ds             */
		if (proFT[now_process][bx1].current_size >= proFT[now_process][bx1].size) {
			ret_val = -1;
			al1 = 0;
		} else {
			/* al1 = read_file(proFT[now_process][bx1].current_cluster, proFT[now_process][bx1].current_pointer); */
			al1 = read_char(now_process, bx1);
			asm push ds
			asm mov ax, dx1
			asm mov ds, ax
			asm mov bx, cx1
			asm mov al, al1
			asm mov [bx], al
			asm pop ds
			/*
			puts_no_new_line("clu=");
			printint(proFT[now_process][bx1].current_pointer);
			puts_no_new_line("siz=");
			printint(proFT[now_process][bx1].current_size);
			*/
			++ proFT[now_process][bx1].current_pointer;
			++ proFT[now_process][bx1].current_size;
			if (proFT[now_process][bx1].current_pointer == 0x200) {
				proFT[now_process][bx1].current_pointer = 0;
				proFT[now_process][bx1].current_cluster = next_cluster(proFT[now_process][bx1].current_cluster);
				read_file(now_process, bx1);
			}
			ret_val = 0;
		}
	} else
	if (ah1 == 0x02) {
		/* fputbyte */
		/* al1 = w              */
		/* bx1 = f_id           */
		/* write_file(proFT[now_process][bx1].current_cluster, proFT[now_process][bx1].current_pointer, al1); */
		write_char(now_process, bx1, al1);
		++ proFT[now_process][bx1].current_pointer;
		++ proFT[now_process][bx1].current_size;
		++ proFT[now_process][bx1].size;
		if (proFT[now_process][bx1].current_pointer == 0x200) {
			write_file(now_process, bx1);
			proFT[now_process][bx1].current_pointer = 0;
			proFT[now_process][bx1].current_cluster = available_cluster(proFT[now_process][bx1].current_cluster);
		}
		ret_val = 0;
	} else
	if (ah1 == 0x03) {
		/* fclose */
		/* bx1 = f_id           */
		delFileTable(now_process, bx1);
		ret_val = 0;
	}
	return ret_val;
}
