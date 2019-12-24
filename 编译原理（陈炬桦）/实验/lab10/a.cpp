#include <bits/stdc++.h>

#define N 20

using namespace std;

int n, first[N][N], last[N][N], firstp[N][N], lastp[N][N], eq[N][N], lt[N][N], gt[N][N];
char st[N], c[N];
char ans[N][N];

int get(char x) {
	for (int i = 1; i <= n; ++i)
		if (c[i] == x)
			return i;
	return 0;
}

void mul(int c[][N], const int a[][N], const int b[][N]) {
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			c[i][j] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k)
				if (a[i][k] && b[k][j]) {
					c[i][j] = 1;
					break;
				}
		}
}

int main() {
#ifdef DEBUG
	freopen("a.in", "r", stdin);
#endif
	scanf("%s", st);
	int n1 = 0, n2 = 0;
	scanf("%d", &n1);
	for (int i = 1; i <= n1; ++i) {
		scanf("%s", st);
		c[i] = st[0];
	}
	scanf("%d", &n2);
	for (int i = n1 + 1; i <= n1 + n2; ++i) {
		scanf("%s", st);
		c[i] = st[0];
	}
	n = n1 + n2;
	int m;
	scanf("%d", &m);
	while (m--) {
		int id;
		scanf("%d", &id);
		char xx;
		scanf("%s", st);
		xx = st[0];
		scanf("%s", st);
		int len = strlen(st);
		int x = get(xx);
		int y1 = get(st[0]);
		int y2 = get(st[len - 1]);
		for (int i = 0; i < len - 1; ++i) {
			int x1 = get(st[i]);
			int x2 = get(st[i + 1]);
			eq[x1][x2] = 1;
		}
		first[x][y1] = 1;
		firstp[x][y1] = 1;
		last[x][y2] = 1;
		lastp[x][y2] = 1;
	}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (firstp[i][k] && firstp[k][j])
					firstp[i][j] = 1;
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (lastp[i][k] && lastp[k][j])
					lastp[i][j] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (eq[i][j])
				ans[i][j] = '=';
	puts("EQUAL=");
	printf("   ");
	for (int i = 1; i <= n; ++i) printf("%3c", c[i]);
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%3c", c[i]);
		for (int j = 1; j <= n; ++j)
			printf("%3d", eq[i][j]);
		puts("");
	}
	mul(lt, eq, firstp);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (lt[i][j])
				ans[i][j] = '<';
	puts("LEQUAL=");
	printf("   ");
	for (int i = 1; i <= n; ++i) printf("%3c", c[i]);
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%3c", c[i]);
		for (int j = 1; j <= n; ++j)
			printf("%3d", lt[i][j]);
		puts("");
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < i; ++j)
			swap(lastp[i][j], lastp[j][i]);
	for (int i = 1; i <= n; ++i) firstp[i][i] = 1;
	mul(gt, lastp, eq);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			lastp[i][j] = gt[i][j];
	mul(gt, lastp, firstp);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (gt[i][j])
				ans[i][j] = '>';
	puts("GEQUAL=");
	printf("   ");
	for (int i = 1; i <= n; ++i) printf("%3c", c[i]);
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%3c", c[i]);
		for (int j = 1; j <= n; ++j)
			printf("%3d", gt[i][j]);
		puts("");
	}
	puts("M[R]=");
	printf("   ");
	for (int i = 1; i <= n; ++i) printf("%3c", c[i]);
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%3c", c[i]);
		for (int j = 1; j <= n; ++j)
			if (ans[i][j] == '<' || ans[i][j] == '=' || ans[i][j] == '>')
				printf("%3c", ans[i][j]);
			else
				printf("   ");
		puts("");
	}
}
