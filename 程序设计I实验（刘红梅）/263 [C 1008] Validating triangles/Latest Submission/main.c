#include <stdio.h>
int main() {
  int a[3], t;
  for (int i=0;i<3;i++) scanf("%d", &a[i]);
  for (int i=0;i<3;i++)
    	for (int j=i+1;j<3;j++) if (a[i] > a[j]) t=a[i],a[i]=a[j],a[j]=t;
  if (a[0]+a[1]<=a[2]) puts("invalid"); else puts("valid");
}