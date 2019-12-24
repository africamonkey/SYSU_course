#include <bits/stdc++.h>

#define N 20

using namespace std;

int n, g1[N][N], g2[N][N];
char st[N], c[N];

int get(char x) {
	for (int i = 1; i <= n; ++i)
		if (c[i] == x)
			return i;
	return 0;
}

int main() {
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
		g1[x][y1] = 1;
		g2[x][y2] = 1;
	}
	puts("FIRST=");
	printf("   ");
	for (int i = 1; i <= n; ++i) printf("%3c", c[i]);
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%3c", c[i]);
		for (int j = 1; j <= n; ++j)
			printf("%3d", g1[i][j]);
		puts("");
	}
	puts("LAST=");
	printf("   ");
	for (int i = 1; i <= n; ++i) printf("%3c", c[i]);
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%3c", c[i]);
		for (int j = 1; j <= n; ++j)
			printf("%3d", g2[i][j]);
		puts("");
	}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (g1[i][k] && g1[k][j])
					g1[i][j] = 1;
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (g2[i][k] && g2[k][j])
					g2[i][j] = 1;
	puts("FIRST+=");
	printf("   ");
	for (int i = 1; i <= n; ++i) printf("%3c", c[i]);
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%3c", c[i]);
		for (int j = 1; j <= n; ++j)
			printf("%3d", g1[i][j]);
		puts("");
	}
	puts("LAST+=");
	printf("   ");
	for (int i = 1; i <= n; ++i) printf("%3c", c[i]);
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%3c", c[i]);
		for (int j = 1; j <= n; ++j)
			printf("%3d", g2[i][j]);
		puts("");
	}
}
