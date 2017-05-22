#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int id;
  char a[2];
  char b[15];
  char c[15];
  int d;
} Node;

int cmp0(Node a,Node b) {
	return a.id > b.id;
}

int cmp1(Node a, Node b) {
	if (strcmp(a.a, b.a)==0) return strcmp(a.c, b.c) > 0;
	return strcmp(a.a, b.a) > 0;
}

int cmp2(Node a, Node b) {
	if (strcmp(a.b, b.b)==0) return strcmp(a.c, b.c) > 0;
	return strcmp(a.b, b.b) > 0;
}

int cmp3(Node a, Node b) {
	return strcmp(a.c, b.c) > 0;
}

int cmp4(Node a, Node b) {
	if (a.d==b.d) return strcmp(a.c, b.c) > 0;
	return a.d < b.d;
}

int cmp(Node a, Node b, int c) {
	if (c==0) return cmp0(a,b);
	if (c==1) return cmp1(a,b);
	if (c==2) return cmp2(a,b);
	if (c==3) return cmp3(a,b);
	return cmp4(a,b);
}

Node a[10020];
int n;

int main() {
	scanf("%d", &n);
  for (int i=1;i<=n;i++) {
  	a[i].id = i;
  	scanf("%s%s%s%d", a[i].a, a[i].b, a[i].c, &a[i].d);
  }
  int m;
  scanf("%d", &m);
  while (m != -1) {
  	
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++) if (cmp(a[i],a[j],m)) {
			Node t; t=a[i]; a[i]=a[j];a[j]=t;
		  }

	printf("Gender Name   Id       Score\n");
	for (int i=1;i<=n;i++) {
		printf("%-7s%-7s%-9s%-5d\n", a[i].a, a[i].b, a[i].c, a[i].d);
	}
  	scanf("%d", &m);
  	puts("");
  }
  
}