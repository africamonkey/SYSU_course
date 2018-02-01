#include <stdio.h>
#include <string.h>
int main() {
  char st[100];
  scanf("%s",st);
  int len=strlen(st);
  unsigned int ans=0;
  for (int i=0;i<len;i++) ans=ans*2+(st[i]-'0');
  printf("%u\n",ans);
}