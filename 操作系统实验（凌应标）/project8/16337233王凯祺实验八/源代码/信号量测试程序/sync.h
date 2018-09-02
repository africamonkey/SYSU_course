int getSem(int init_val) {
	asm mov ah, 00h
	asm mov dx, init_val
	asm int 25h       /* return ax */
}

void P(int sem_id) {
	asm mov ah, 01h
	asm mov dx, sem_id
	asm int 25h
}

void V(int sem_id) {
	asm mov ah, 02h
	asm mov dx, sem_id
	asm int 25h
}

void freeSem(int sem_id) {
	asm mov ah, 03h
	asm mov dx, sem_id
	asm int 25h
}