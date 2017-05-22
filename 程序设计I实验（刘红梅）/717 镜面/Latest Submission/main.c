#include <stdio.h>
char st[102];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i=0;i<n;i++) {
    scanf("%s", st);
    for (int j=0;j<m/2;j++) {
      char t;
      t=st[j];st[j]=st[m-1-j];st[m-1-j]=t;
    }
    for (int j=0;j<m;j++)
      	if (st[j]=='b') st[j]='d';
    else if (st[j]=='d') st[j] = 'b';
    puts(st);
  }
}