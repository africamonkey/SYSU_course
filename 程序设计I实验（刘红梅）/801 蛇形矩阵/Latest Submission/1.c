#include <stdio.h>

int n, a[102][102];

int main() {
	scanf("%d", &n);
	int t = 0;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=i;j++)
			a[i-j+1][j] = ++t;
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n-i+1;j++)
			printf("%4d", a[i][j]);
		puts("");
	}
}