#include <stdio.h>
#include <math.h>
int main() {
  double a, b, c;
  scanf("%lf%lf%lf", &a, &b, &c);
  b = b / 12;
  c = c * 12;
  b = b/100.0 + 1;
  b = pow(b, c);
  a = a * b;
  printf("%.2lf\n", a);
}