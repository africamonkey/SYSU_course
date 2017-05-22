#include <stdio.h>
#include <string.h>
char st[100020];
int main() {
  scanf("%s", st);
  while (~scanf("%s", st)) {
    int len = strlen(st);
    int ok = 1;
    for (int i=0;i<len/2;i++)
      if (st[i] != st[len-1-i]) ok = 0;
    puts(ok ? "Yes": "No");
  }
}