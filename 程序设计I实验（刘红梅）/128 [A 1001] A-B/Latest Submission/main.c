#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *gets(char *str);
int main() {
  	char st[100];
	fgets(st, sizeof st, stdin);
  	int a, b;
  	sscanf(st, "%d%d", &a, &b);
  	printf("%d\n", a-b);
  	return 0;
}