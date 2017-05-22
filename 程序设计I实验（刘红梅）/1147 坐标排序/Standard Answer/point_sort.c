#include "point_sort.h"

void point_sort(struct point a[], int n) {
	for (int i = 0; i < n-1; ++i) {
		for (int j = 0; j < n-1-i; ++j) {
			if (a[j].x > a[j+1].x || (a[j].x == a[j+1].x && a[j].y > a[j+1].y)) {
				struct point temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}