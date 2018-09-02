extern void lprintf();
extern void prom1();
extern void time();
extern void mmdate();
extern void lprintf2();
extern void Low2Up();
extern void reboot();
extern void ReadCommand();
extern void RunProm(int);
extern void checkup();
extern void printf();
extern void cprintf();
extern void lock();
extern void unlock();
extern void loaderpro(int,int,int);
extern void loader(int,int);

char* cpointer;
int num=0;
char bb[5]="00000";
char CMDline[30]="aaaaaaaaaaaaaaaaaaaa";
char Message[30]="OSaaabbbAaBbCcDdEe";     /*变量_Message,初值为AaBbCcDdEe*/
char help[80]="a for asc number,t for time d for date,f for file list,1234 for user programe";
char f[40]="num  name      size      position";
int jj=0;
int i=0;
char ttime[20]="";
char ddate[20]="";
char aa[5]="";
int aanum=0;
int disp_pos=0;
struct pcb* CurrentProc;

typedef struct pcb
{
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
	char p_name;
};
struct pcb PCBlist[5];

struct file
{
	char num[5];
	char name[10];
	char size[10];
	char pos[10];	
}filelist[5]={{"1","PRO1    ","3037bit","2000h"},{"2","PRO2    ","3224bit","2200h"},{"3","PRO3    ","3244bit","2400h"},{"4","PRO4    ","781bit","2600h"},
{"5","TEXT    ","781bit","2600h"}};

iniPCB(int index)
{
	int temp=0x8000;
	PCBlist[index].cs=temp-index*0x1000;
	PCBlist[index].ip=0x100;
	PCBlist[index].flags=512;
	PCBlist[index].status=1;
	PCBlist[index].p_name='1'+index;
	return;
}

upper(){
   int i=0;
   while(Message[i]) {
     if (Message[i]>='a'&&Message[i]<='z')  
      Message[i]=Message[i]+'A'-'a';
	  i++;
    }
}

pro2()
{	
	lprintf();
}

printnum(int number)
{
	int t;
	t=number/10;
	t=t%10;
	printChar(t+'0');
	t=number%10;
	printChar(t+'0');
	return;
}

int findpro(int index)
{
	int i=0,j=0,k=0,firnum=0;
	char im[10]="Not Found";
	char* t;
	disp_pos=5*80*2;
	for(;i<14;i++)
	{
		loader(i+19,0);
		j=0;
		for(;j<16;j++)
		{
			t=cpointer;
			k=0;
			for(;k<8;k++)
			{
				if(filelist[index].name[k]!=*t) break;
				else t++;
			}
			if(k==8) 
			{
				unsigned char* temp=cpointer;
				firnum=(*(temp+27))*256+(*(temp+26));
				return firnum;
			}
			cpointer+=32;
		}
	}
	printf(im);
	return 0;
}

loadpro(int fir,int index)
{
	unsigned char* tem;
	int temp,tt,i=1;
	for(;i<10000;i++)
	{
		temp=(fir*12)/(512*8);
		tt=((fir*12)%(512*8))/8;
		loader(temp+2,1);
		loader(temp+1,0);
		tem=cpointer;
		if(fir%2==0)
		{
			fir=(*(tem+tt))+((*(tem+1+tt))%16)*256;
		}
		else
		{
			fir=(*(tem+tt))/16+(*(tem+1+tt))*16;
		}
		if(fir>=0xFF8) return;
		else loaderpro(31+fir,i,index);
	}
	return;
}

select()
{
	int i,j=0;
	if(CurrentProc==PCBlist) i=0;
	else if(CurrentProc==PCBlist+1) i=1;
	else if(CurrentProc==PCBlist+2) i=2;
	else if(CurrentProc==PCBlist+3) i=3;
	else i=3;
	for(;j<4;j++)
	{
		if(i==3) 
		{
			CurrentProc=PCBlist;
			i=0;
		}
		else 
		{
			CurrentProc++;
			i++;
		}
		if(CurrentProc->status!=0)
			return;
	}
	CurrentProc=PCBlist+4;
	return;
}

cmd()
{
	int i=0;
	lock();
	CurrentProc=PCBlist+4;
	ReadCommand();
	for(;i<4;i++) PCBlist[i].status=0;
	num=0;
        if(CMDline[num]>='1'&&CMDline[num]<='4')
        {
		while(CMDline[num]>='1'&&CMDline[num]<='4')
		{
        		if(CMDline[num]=='1')
        		mypro1();
        		else if(CMDline[num]=='2')
        		mypro2();
        		else if(CMDline[num]=='3')
        		mypro3();
				else if(CMDline[num]=='4')
        		mypro4();
			num++;
		}
		unlock();
		num=0;
		for(jj=0;jj<30;jj++)
		CMDline[jj]='a';
        }
	else if(CMDline[num]=='5')
	{
		mypro5();
	}
	else if(CMDline[num]=='d')
	{
		mydate();
	}
	else if(CMDline[num]=='t')
	{	
		mytime();
	}
	else if(CMDline[num]=='a')
	{
		myasc();
	}
	else if(CMDline[num]=='f')
	{
		myfilelist();
	}
	else if(CMDline[num]=='h')
	{
		disp_pos=3*80*2;
		printf(help);
	}
	reboot();
	return;
}

mypro1()
{
	int firnum;
	firnum=findpro(0);
	if(firnum==0) return;
	loaderpro(31+firnum,0,0);
	loadpro(firnum,0);
	bb[0]='1';
	iniPCB(0);
	return;
}

		
mypro2()
{
	int firnum;
	firnum=findpro(1);
	if(firnum==0) return;
	loaderpro(31+firnum,0,1);
	loadpro(firnum,1);
	bb[0]='2';
	iniPCB(1);
	return;
}

mypro3()
{
	int firnum;
	firnum=findpro(2);
	if(firnum==0) return;
	loaderpro(31+firnum,0,2);
	loadpro(firnum,2);
	bb[0]='3';
	iniPCB(2);
	return;
}

mypro4()
{
	int firnum;
	firnum=findpro(3);
	if(firnum==0) return;
	loaderpro(31+firnum,0,3);
	loadpro(firnum,3);
	bb[0]='4';
	iniPCB(3);
	return;
}

mypro5()
{
	int firnum;
	firnum=findpro(4);
	if(firnum==0) return;
	loaderpro(31+firnum,0,4);
	loadpro(firnum,4);
	bb[0]='5';
	RunProm(4);
	return;
}


mytime()
{
time();
}

mydate()
{
mmdate();
}

myasc()
{
lprintf2();
aanum=65+aa[0]-'A';
Low2Up();	
return;
}

myfilelist()
{
	disp_pos=5*80*2;
	printf(f);
	for(i=0;i<5;i++)
	{
		disp_pos=(6+i)*80*2;
		printf(filelist[i].num);
		disp_pos=(6+i)*80*2+10;
		printf(filelist[i].name);
		disp_pos=(6+i)*80*2+30;
		printf(filelist[i].size);
		disp_pos=(6+i)*80*2+50;
		printf(filelist[i].pos);
	}
	return;
}

change(unsigned char* t)
{
	int a,b,num=*t;
	a=num/16;
	b=(*t)%16;
	if(a>9) printChar('A'+a-10);
	else printChar('0'+a);
	if(b>9) printChar('A'+b-10);
	else printChar('0'+b);
}

int33()
{
	int i=0;
	for(;i<20;i++) CMDline[i]=0;
	cls();
	disp_pos=3*80*2;
	printf("Please enter the word in upper case, the output will be the word in lower case");
	ReadCommand();
	disp_pos=6*80*2;
	i=0;
	while(CMDline[i])
	{
		printChar(CMDline[i]+'a'-'A');
		i++;
	}
	getChar();
	return;
}

int34()
{
	int i=0;
	unsigned char* t;
	for(;i<20;i++) CMDline[i]=0;
	cls();
	disp_pos=3*80*2;
	printf("Please enter a word, the output will be its ASCII number");
	ReadCommand();
	disp_pos=6*80*2;
	i=0;
	while(CMDline[i])
	{
		t=CMDline+i;
		change(t);
		printChar(' ');
		i++;
	}
	getChar();
	return;
}

int35()
{
	int i=0;
	unsigned char* t;
	for(;i<20;i++) CMDline[i]=0;
	cls();
	disp_pos=3*80*2;
	printf("Please enter a simple expression(It should have two numbers and one operator and the number must only have one digit)");
	ReadCommand();
	disp_pos=6*80*2;
	if(CMDline[1]=='+') printnum(CMDline[0]-'0'+CMDline[2]-'0');
	else if(CMDline[1]=='-') printnum(CMDline[0]-CMDline[2]);
	else if(CMDline[1]=='*') printnum((CMDline[0]-'0')*(CMDline[2]-'0'));
	else if(CMDline[1]=='/') printnum((CMDline[0]-'0')/(CMDline[2]-'0'));
	getChar();
	return;
}

int36()
{
	int i;
	if(CurrentProc==PCBlist) i=0;
	else if(CurrentProc==PCBlist+1) i=1;
	else if(CurrentProc==PCBlist+2) i=2;
	else if(CurrentProc==PCBlist+3) i=3;
	PCBlist[i].status=0;
	return;
}
