#include <stdio.h>

int n, m, top, t;
int c[10020], aa[10020], bb[10020];

int main() {
	scanf("%d%d", &n, &m);
	int k = 2 * m;
	top = 0;
	for (int i=1;i*i<=k;i++) {
		if (k % i == 0)
			c[++top] = i;
	}
	int l = top;
	for (int i=l;i>=1;i--) {
		if (c[i] * c[i] != k) {
			c[++top] = k / c[i];
		}
	}
	t = 0;
	for (int i=1;i<=top;i++) {
		int d = k / c[i]; //d = a + b, c[i] = b - a + 1
		int a = -c[i] + d + 1;
		if (a % 2) continue;
		a /= 2;
		int b = c[i] + d - 1;
		if (b % 2) continue;
		b /= 2;
		if (a >= 1 && b <= n && a <= b) {
			aa[++t] = a; bb[t] = b;
		}
	}
	for (int i=1;i<=t;i++)
		for (int j=i+1;j<=t;j++)
			if (aa[i] > aa[j]) {
				int tt = aa[i]; aa[i] = aa[j]; aa[j] = tt;
				tt = bb[i]; bb[i] = bb[j]; bb[j] = tt;
			}
	for (int i=1;i<=t;i++) {
		printf("[%d,%d]\n", aa[i], bb[i]);
	}
}