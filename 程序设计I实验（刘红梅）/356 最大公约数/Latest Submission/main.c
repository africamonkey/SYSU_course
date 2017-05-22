#include <stdio.h>
int gcd(int x, int y) {
  int r;
  while (y) {
  	r = x % y;
    x = y;
    y = r;
  }
  return x;
}
int main() {
  int x, y;
  scanf("%d%d", &x, &y);
  printf("%d\n", gcd(x, y ));
}