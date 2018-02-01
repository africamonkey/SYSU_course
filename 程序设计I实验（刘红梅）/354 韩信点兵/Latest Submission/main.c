#include <stdio.h>
int main() {
  int x, y, z;
  scanf("%d%d%d", &x, &y, &z);
  for (int i=1;i<=100000;i++)
    if (i%3==x && i%5==y && i%7==z) {
      printf("%d\n", i);
      break;
    }
}