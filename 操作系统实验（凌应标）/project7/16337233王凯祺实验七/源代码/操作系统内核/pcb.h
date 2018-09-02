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
	char pname[16];
};

const int DEAD = 0;
const int READY = 1;
const int RUNNING = 2;
const int BLOCK = 3;