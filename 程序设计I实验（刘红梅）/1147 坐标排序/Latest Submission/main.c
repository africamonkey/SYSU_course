#include <stdio.h>
#include "point_sort.h"


int main() {
	struct point a[100];
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	point_sort(a, n);
	for (int i = 0; i < n; ++i) {
		printf("%d %d\n", a[i].x, a[i].y);
	}
}