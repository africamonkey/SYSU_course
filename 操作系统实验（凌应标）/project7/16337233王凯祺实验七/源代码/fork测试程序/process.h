void exit(int ret_val) {
	char tmp;
	tmp = ret_val;
	asm mov ah, 4ch
	asm mov al, tmp
	asm int 21h
}

int fork() {
	asm int 22h
}

int wait() {
	asm int 23h
}