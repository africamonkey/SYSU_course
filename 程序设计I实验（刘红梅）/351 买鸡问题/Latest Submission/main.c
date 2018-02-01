#include <stdio.h>
int main() {
	int ok = 0;
  int m, n;
  scanf("%d%d", &m, &n);
  for (int i=300;i>=0;i--)
    for (int j=300;j>=0;j--)
      for (int k=n-i-j;k>=0 && k >= n-i-j;k--) {
        if (k%3==0 && 5*i+3*j+k/3==m) {
          ok = 1;
          printf("%d %d %d\n", i, j, k);
        }
      }
 if (!ok) puts("no answer");
}