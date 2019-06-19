extern char incr();
extern void cprintf();
extern void printf();

char buffer[50]="HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n";
char ccch='T';
int disp_pos=0;
char buffer1[50]="LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n";
cmain(){
/*	char buf[15]="hello world!";  */
	cls();
	printChar(ccch);
	printChar('R');
	cprintf(buffer1,230); 
	printf(buffer); 
}
