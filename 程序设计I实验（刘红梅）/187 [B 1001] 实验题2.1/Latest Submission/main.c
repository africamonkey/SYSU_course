#include <stdio.h>
#include <math.h>
int main() {
  	int a, b, c;
	double x, y;
  	scanf("%d%d%d%lf%lf", &a, &b, &c, &x, &y);
  	printf("%.3lf\n%.3lf\n%.3lf\n%.3lf\n", 300.0, (double)c*(double)sqrtl(a*a+b*b), 2.087, y+a%5*(int)(x+y)/2%4);
	return 0;
}