void halt() {
	asm mov ah, 4ch
	asm mov al, 0h
	asm int 21h
}

