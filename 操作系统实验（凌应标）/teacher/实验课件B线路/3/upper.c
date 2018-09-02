/*程序源代码（upper.c）*/
char Message[18]="OSaaabbbAaBbCcDdEe";     /*变量_Message,初值为AaBbCcDdEe*/
upper(){
   int i=0;
   while(Message[i]) {
     if (Message[i]>='a'&&Message[i]<='z')  
      Message[i]=Message[i]+'A'-'a';
	  i++;
    }
}