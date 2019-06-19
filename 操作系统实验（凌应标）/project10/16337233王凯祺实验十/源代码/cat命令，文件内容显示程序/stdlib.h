void exit(int ret_val) {
	char tmp;
	tmp = ret_val;
	asm mov ah, 4ch
	asm mov al, tmp
	asm int 21h
}

void halt() {
	exit(0);
}

int fork() {
	asm int 22h
}

int wait() {
	asm int 23h
}

void sleep(int sleeptime) {
	asm push ax
	asm mov ax, sleeptime
	asm int 24h
	asm pop ax
}

void getParameter(int pa_ds, char *parameter) {
	int ip;
	ip = parameter;
	asm push ax
	asm push bx
	asm push dx
	asm mov ah, 01h
	asm mov bx, ip
	asm mov dx, pa_ds
	asm int 21h
	asm pop dx
	asm pop bx
	asm pop ax
}