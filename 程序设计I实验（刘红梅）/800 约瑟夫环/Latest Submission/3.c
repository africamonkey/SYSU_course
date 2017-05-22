#include <stdio.h>

int n, m;

int main() {
	scanf("%d%d", &n, &m);
	int res = 0;
	for (int i=1;i<=n;i++) {
		res = (res + m) % i;
	}
	res ++;
	printf("%d\n", res);
}