#include <stdio.h>
int main() {
	char st[5];
	scanf("%s", st);
  	st[1] = st[2] = st[3] = st[0]; st[4] = 0;
  	for (int i=3;i>=0;i--) {
      for (int j=0;j<i;j++) printf(" ");
      printf("%s\n", st);
    }
  return 0;
}