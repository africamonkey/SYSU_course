#include <stdio.h>
int count(int x) {
  int a = 0;
  for (; ; ) {
    a++;
    if (x==1) return a;
    if (x%2) x=3*x+1; else x/=2;
  }
  return a;
}
int main() {
  int i, j;
  scanf("%d%d", &i, &j);
  int mx = 0;
  for (int k=i;k<=j;k++) {
    int t = count(k);
    if (t > mx) mx = t;
  }
  printf("%d\n", mx);
}