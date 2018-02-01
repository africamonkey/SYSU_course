#include "point_sort.h"

int cmp (struct point x, struct point y) {
  if (x.x != y.x) return x.x < y.x;
  return x.y < y.y;
}

void point_sort(struct point a[], int n) {
   for (int i=0;i<n;i++)
     	for (int j=i;j<n;j++)
        	if (!cmp(a[i] , a[j])) {
            struct point t;
            t = a[i];
            a[i] = a[j];
            a[j] = t;
          }
 }