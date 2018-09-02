#ifndef _PCB

#define _PCB

#include "stdcon.h"

typedef struct PCB {
	int ax;
	int bx;
	int cx;
	int dx;
	int si;
	int di;
	int bp;
	int es;
	int ds;
	int ss;
	int sp;
	int ip;
	int cs;
	int flags;
	int status;
	int father_pid;
	int son_cnt;
	int ret_val;
	char pname[MAX_EXENAME_LEN];
	char parameter[MAX_PARAMETER_LEN];
};

#define DEAD 0
#define READY 1
#define RUNNING 2
#define BLOCK 3

#endif