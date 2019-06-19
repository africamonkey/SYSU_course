int getSem(int init_val) {
	asm push dx
	asm mov ah, 00h
	asm mov dx, init_val
	asm int 25h       /* return ax */
	asm pop dx
}

void P(int sem_id) {
	asm push ax
	asm push dx
	asm mov ah, 01h
	asm mov dx, sem_id
	asm int 25h
	asm pop dx
	asm pop ax
}

void V(int sem_id) {
	asm push ax
	asm push dx
	asm mov ah, 02h
	asm mov dx, sem_id
	asm int 25h
	asm pop dx
	asm pop ax
}

void freeSem(int sem_id) {
	asm push ax
	asm push dx
	asm mov ah, 03h
	asm mov dx, sem_id
	asm int 25h
	asm pop dx
	asm pop ax
}