#include <stdio.h>
#include <math.h>
int main() {
  double a, b, c;
  scanf("%lf%lf%lf", &a, &b, &c);
  if (a < 0) a = -a, b = -b, c = -c;
  printf("%.3lf %.3lf\n", (-b-sqrt(b*b-4*a*c))/(2*a), (-b+sqrt(b*b-4*a*c))/(2*a));
}