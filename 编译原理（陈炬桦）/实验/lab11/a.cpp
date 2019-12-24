#include <bits/stdc++.h>

#define N 100

using namespace std;

int n, g[N][N], v[N], A[N][N], B[N];
char t[N], d[N][N];

void dfs(int x) {
	if (v[x]) return;
	v[x] = 1;
	for (int i = 1; i <= n; ++i)
		if (g[x][i])
			dfs(i);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		char st[100];
		scanf("%s", st);
		t[i] = st[0];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			char st[100];
			scanf("%s", st);
			d[i][j] = st[0];
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			if (d[i][j] == '>' || d[i][j] == '=') g[i][j + n] = 1;
			if (d[i][j] == '<' || d[i][j] == '=') g[j + n][i] = 1;
		}
	n *= 2;
	for (int i = 1; i <= n; ++i) {
		memset(v, 0, sizeof(v));
		dfs(i);
		for (int j = 1; j <= n; ++j)
			if (v[j]) {
				A[i][j] = 1;
				B[i] += 1;
			}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%3d", B[i]);
		for (int j = 1; j <= n; ++j)
			printf("%3d", A[i][j]);
		puts("");
	}
	printf("   ");
	for (int i = 1; i <= n / 2; ++i) printf("%3c", t[i]);
	puts("");
	printf("  f");
	for (int i = 1; i <= n / 2; ++i) printf("%3d", B[i]);
	puts("");
	printf("  g");
	for (int i = n / 2 + 1; i <= n; ++i) printf("%3d", B[i]);
	puts("");
}
