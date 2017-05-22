#include <stdio.h>

int tot, n;

void work(int n, int p1, int p2) {
	if (!n) return;
	work(n-1, p1, 6-p1-p2);
	printf("move disk %d from peg %d to peg %d\n", n, p1, p2);
	work(n-1, 6-p1-p2, p2);
}

int main() {
	scanf("%d", &tot);
	while (tot--) {
		scanf("%d", &n);
		work(n, 1, 3);
	}
}