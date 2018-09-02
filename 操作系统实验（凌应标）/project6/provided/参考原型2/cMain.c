extern void printChar();
extern void getChar();
extern void show_Time();
extern void show_Date();
extern void cls();
extern void Run();
extern void Int33();
extern void Int34();
extern void Int35();
extern void Int36();
extern void Fun_Upper(char* word);
extern void Fun_Lower(char* word);
extern int  String_to_Num(char* word);
extern void Num_to_String(int word);
extern void Binary_to_Decimal(char* word);
extern void Print_String( char* word,char row,char col );
extern void Load_Int21();
extern void Print_CoLor_String( char* word,char row,char col );
extern int  If_Equal( char* word1,char* word2 );
extern void Show_Orch();
extern void setClock();
extern void another_load(int segment,int offset);
extern void Open_Key_Int();
extern void Close_Key_Int();
#include "kdata.h"

#define BUFLEN 1000
char *disp_pos;
char input;
char Buffer[BUFLEN];
char TempBuffer[BUFLEN];


int index;
char century,year,month,day;
char hour,minute,second;
int century1,year1,month1,day1;
int hour1,minute1,second1;
int i,j;
int bl;
int ASCII_Num;
char Pro;
char Function_Num;
int StringLen;
int StringLen2;
int Num;
char row,col;
int dir;
int Segment = 0x2000;

void GetInput();
void Print( char* word );
int check( char* word,char* goal );
void Transfor( int num );
void PrintTime();
void PrintDate();
void Initial();
void CheckASCII();
void RunProgram();
void PrintIns();
int BCDdecode( int n );
void Print_Int( int n );
void Bin_to_Dec( char* word );
char String_to_Int( char* word );
void GetInput2();
void Call_Int21();
void start();
int String_to_Int2( char* word );
int If_NumString( char* word );
int If_Binary( char* word );
void Random_Load();
void init_Pro();
void Delay();


void cmain()
{
	cls();
	Load_Int21();
	Initial();
	setClock();
	while(1)
	{
		print("\n>>>");
		GetInput();
		init_Pro();
		if( check( Buffer,"time" ) )
		{
			show_Time();
			PrintTime();
		}
		else if( check( Buffer,"date" ) )
		{
			show_Date();
			PrintDate();
		}
		else if( check( Buffer,"cls") )
		{
			cls();
			Initial();
		}
		else if( check( Buffer,"ascii") )
			CheckASCII();
		else if( check( Buffer,"pro" ) )
		{
			Print("Key in the program you want to excute(1-5, 5 is a test for interupt): ");
		       	GetInput();
			cls();
			Random_Load();
			Delay();
			cls();
			Initial();
		}
		else if( check ( Buffer,"help" ) )
			PrintIns();
		else if( Buffer[0] == '\0' )
			continue;
		else if( check(Buffer,"int21") )
		{
			Call_Int21();
			cls();
			Initial();
		}
		else
		{
			Print("\nInvalid Instruction!\r\n");
			Print("You can key in \"help\" to check the specific command!\r\n");
		}
	}
}




void GetInput()
{
	index = 0;
	getChar();
	printChar(input);
	while( input != '\n'&& input != '\r' )
	{
		Buffer[index] = input;
		index ++;
		getChar();
		printChar(input);
	}
	Buffer[index] = '\0';
	Print("\n");
	StringLen = index;
}

void GetInput2()
{
	index = 0;
	getChar();
	printChar(input);
	while( input != '\n'&& input != '\r' )
	{
		TempBuffer[index] = input;
		index ++;
		getChar();
		printChar(input);
	}
	TempBuffer[index] = '\0';
	Print("\n");
	StringLen2 = index;
}

void Print( char* word )
{
	while( *word != '\0' )
	{
		printChar( *word );
		word ++ ;
	}
}



int check( char *word,char* goal )
{
	while(*word != '\0' && *goal != '\0')
	{
		if( *word != *goal )
			return 0;
		else
		{
			word ++;
			goal ++;
		}
	}
	if( *word == '\0' && *goal == '\0' )
		return 1;
	return 0;
}


int BCDdecode(int n) {
    return n / 16 * 10 + n % 16;
}

void Transfor( int num )
{
	Buffer[0] = num/10 + '0';
	Buffer[1] = num%10 + '0';
	Buffer[2] = '\0';
}

void PrintTime()
{
	hour1 = hour;
	minute1 = minute;
	second1 = second;

	Print("\nTime: ");
	Transfor( BCDdecode(hour1) );
	Print(Buffer);
	Print(":");

	Transfor( BCDdecode(minute1) );
	Print(Buffer);
	Print(":");

	Transfor( BCDdecode(second1) );
	Print(Buffer);
	print("\r\n");
}

void PrintDate()
{
	century1 = century;
	year1 = year;
	month1 = month;
	day1 = day;

	Print("\nDate: ");
	Transfor(BCDdecode(century1));
	Print(Buffer);

	Transfor( BCDdecode(year1) );
	Print(Buffer);
	Print("/");

	Transfor(BCDdecode(month1));
	Print(Buffer);
	Print("/");

	Transfor(BCDdecode(day1));
	Print(Buffer);
	print("\r\n");
}

void Initial()
{
	Print("                        \n\n Welcome to LeeWM-MyOS V6.0!\r\n\n");
	Print("   You can excute some functions by keying commands! If you do not know the\r\n\n"); 
	Print("specific commands,you can key in \"help\" to Query!\r\n");
}

void CheckASCII()
{
	Print("\r\nKey in the character you want to check for ASCII Number:");
	getChar();
	printChar(input);
	ASCII_Num = input;
	Transfor( ASCII_Num );
	Print("\r\nThe ASCII Number of ");
	PrintChar(input);
	Print(" is ");
	Print(Buffer);
	Print(".\r\n");
}


void RunProgram()
{
	int i = 0;
	int j = 0;
	bl = 0;
	Print("Key in the number of program(1-3) you want to excute in any order,and you can\r\n");
	Print("run any amount of programs (like 123 or 2313... ) :");
	GetInput();

	while( Buffer[i] != '\0' )
	{
		if( Buffer[i] == ' ' )
		{
			i++;
			continue;
		}
		else if( Buffer[i] < '1' || Buffer[i] > '3' )
		{
			bl = 1;
			return;
		}
		else
			i++;
	}

	while( Buffer[j] != '\0' )
	{
		if( Buffer[j] == ' ' )
		{
			j++;
			continue;
		}
		if( Buffer[j] >= '1' && Buffer[j] <='3' )
		{
			Pro = Buffer[j] -'0' + 4;
			Run();
			j++;
		}
	}
	return;
}

void PrintIns()
{
	Print("time         - Print the System Time.\r\n");
	Print("date         - Print the System Date.\r\n");
	Print("ascii        - Query the ASCII Number of a character.\r\n");
	Print("cls          - Clear the screen.\r\n");
	Print("pro          - Creat Process and excute Process.\r\n");
	Print("int21        - Call Interupt 21h!\r\n");
}

void Print_Int( int n )
{
	int temp = n;
	int mod = 0;
	int i = 0;
	int j;
	while( temp > 0 )
	{
		mod = temp % 10;
		temp /= 10;
		TempBuffer[i] = mod + '0';
		i++;
	}
	j = i-1;
	for( ;j>=0;j-- )
		printChar( TempBuffer[j] );
}

void Bin_to_Dec( char* word )
{
	int i = 0;
	int num = 0;
	while( word[i] != '\0' )
	{
		num *= 2;
		num += word[i] - '0';
		i++;
	}
	if( num == 0 )
		Print("0");
	Print_Int( num );
}

char String_to_Int( char* word )
{
	int i = 0;
	char temp = 0;
	while( word[i] != '\0' )
	{
		temp *=10;
		temp += word[i] - '0';
		i++;
	}
	return temp;
}
int String_to_Int2( char* word )
{
	int i = 0;
	int temp = 0;
	while( word[i] != '\0' )
	{
		temp *=10;
		temp += word[i] - '0';
		i++;
	}
	return temp;
}
void start()
{
	cls();
	Print("\r\n                        Here is the Interupt 21h ! ");
	Print("\r\n\nFollowing is the function list of the Interupt 21h : ");
	Print("\r\nFun Number                Function Instruction    ");
	Print("\r\n    0          - Show \"OUCH!OUCH!\" in the center");
	Print("\r\n    1          - Transform lower letters in a string into upper leters");
	Print("\r\n    2          - Transform upper letters in a string into lower leters");
	Print("\r\n    3          - Transform a string into a number ");
	Print("\r\n    4          - Transform a number into a string ");
	Print("\r\n    5          - Show a string in any position you want ");
	Print("\r\n    6          - Transform Binary into Decimal ");
	Print("\r\n    7          - Show a color string in any position you want ");
	Print("\r\n    8          - judging whether two strings are equal ");
	Print("\r\n    q          - Quit the Interupt 21h\r\n\n ");
}
void Call_Int21()
{
	start();
	while(1)
	{
		Print("Key in the Function Number : ");
			getChar();
			printChar(input);
			if( input == '0' )
			{
				cls();
				start();
				Show_Orch();
			}
			else if( input == '1' )
			{
				Print("\r\nKey in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				Fun_Upper(Buffer);
				cls();
				start();
				Print("The upper string is : ");
				Print(Buffer);
				Print("\r\n\n");
			}
			else if ( input == '2' )
			{
				Print("\r\nKey in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				Fun_Lower(Buffer);
				cls();
				start();
				Print("The lower string is : ");
				Print(Buffer);
				Print("\r\n\n");
			}
			else if ( input == '3' )
			{
				Print("\r\nKey in the String ( 0 - 32767 ) : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				if( If_NumString( Buffer ) == 0 )
				{
					cls();
					start();
					Print("Invalid Input ! \r\n\n");
					continue;
				}
				Num = String_to_Num(Buffer);
				cls();
				start();
				Print("The number you key in is : ");
			        Print_Int( Num );
				Print("\r\n\n");
			}
			else if ( input == '4' )
			{
				Print("\r\nKey in the Number ( 0 - 32767 ) : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				if( If_NumString( Buffer ) == 0 )
				{
					cls();
					start();
					Print("Invalid Input ! \r\n\n");
					continue;
				}
				cls();
				start();
				Print("The number you key in is : ");
				Num = String_to_Int2(Buffer);
				Num_to_String(Num);
				Print("\r\n\n");
			}
			else if ( input == '5' )
			{
				Print("\r\nKey in the row number(0-24) you want the string to show: ");
				GetInput();
				row = String_to_Int(Buffer);
				Print("Key in the column number(0-79) you want the string to show: ");
				GetInput();
				col = String_to_Int(Buffer);
				Print("Key in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				cls();
				start();
				Print_String( Buffer,row,col );
				Print("\r\n");
			}
			else if ( input == '6' )
			{
				Print("\r\nKey in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				if( If_Binary( Buffer ) == 0 )
				{
					cls();
				        start();
					Print("Invalid Input ! !\r\n\n");
					continue;
				}
				cls();
				start();
				Print("The Decimal Number of the Binary you key in is : ");
			        Binary_to_Decimal(Buffer);
				Print("\r\n\n");
			}
			else if ( input == '7' )
			{
				Print("\r\nKey in the row number you want the color string to show: ");
				GetInput();
				row = String_to_Int(Buffer);
				Print("Key in the column number you want the color string to show: ");
				GetInput();
				col = String_to_Int(Buffer);
				Print("Key in the String : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					continue;
				}
				cls();
				start();
				Print_Color_String( Buffer,row,col );
				Print("\r\n");
			}
			else if ( input == '8' )
			{
				Print("\r\nKey in the String A : ");
				GetInput();
				if( StringLen == 0 )
				{
					cls();
				        start();
					Print(" Not Empty String!  \r\n\n");
					continue;
				}
				Print("Key in thr String B : ");
				GetInput2();
				if( StringLen2 == 0 )
				{
					cls();
				        start();
					Print(" Not Empty String!  \r\n\n");
					continue;
				}
				cls();
				start();
				if( If_Equal(Buffer,TempBuffer)==0 )
					Print("Two strings are not Equal!\r\n\n");
				if( If_Equal(Buffer,TempBuffer)==1 )
					Print("Two strings are Equal!\r\n\n");
			}
			else if ( input == 'q' )
				break;
			else
			{
				cls();
				start();
				Print("\r\nInvalid Input!\r\n");
			}
	}
}

int If_NumString( char* word )
{
	int i = 0;
	while( word[i] != '\0' )
	{
		if( word[i] <'0' || word[i] >'9' )
			return 0;
		i++;
	}
	return 1;
}

int If_Binary( char* word )
{
	int i = 0;
	while( word[i] != '\0' )
	{
		if( word[i] != '0' && word[i] != '1' )
			return 0;
		i++;
	}
	return 1;
}

void Random_Load()
{
	int i = 0;
	int j = 0;
	for( i=0; i<StringLen;i++ )
		if( Buffer[i]!=' ' && (Buffer[i]<'1' || Buffer[i]>'5') )
		{
			Print("Error Input!");
			return;
		}
	for( i=0; i<StringLen;i++ )
	{
		if( Buffer[i] ==' ' )
			continue;
		else
		{
			j = Buffer[i] - '0';
			if( Segment > 0x6000 )
			{
				Print("There have been 5 Processes !");
				break;
			}
			another_load(Segment,j);
			Segment += 0x1000;
			Program_Num ++;
		}
	}
}

void init_Pro()
{
	init(&pcb_list[0],0x1000,0x100);
	init(&pcb_list[1],0x2000,0x100);
	init(&pcb_list[2],0x3000,0x100);
	init(&pcb_list[3],0x4000,0x100);
	init(&pcb_list[4],0x5000,0x100);
	init(&pcb_list[5],0x6000,0x100);
}

void Delay()
{
	int i = 0;
	int j = 0;
	for( i=0;i<30000;i++ )
		for( j=0;j<30000;j++ )
		{
			j++;
			j--;
		}
}
