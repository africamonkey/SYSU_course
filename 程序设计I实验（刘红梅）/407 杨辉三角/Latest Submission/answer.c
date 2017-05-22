#include <stdio.h>
int main() {
  int n;
  scanf("%d", &n);
  if (n < 1 || n > 10) {
    printf("Number %d is Out Of Range.\n", n);
    return 0;
  }
  int c[15][15];
  for (int i=0;i<15;i++) c[i][i]=c[i][0]=1;
  for (int i=0;i<15;i++)
    for (int j=1;j<i;j++)
      c[i][j] = c[i-1][j-1] + c[i-1][j];
  for (int i=0;i<n;i++)
    for (int j=0;j<=i;j++) {
      printf("%d",c[i][j]);
      if (j==i) printf("\n"); else printf(" ");
    }
}