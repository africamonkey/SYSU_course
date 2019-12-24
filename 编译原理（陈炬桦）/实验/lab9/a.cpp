#include <bits/stdc++.h>

#define N 10

using namespace std;

int n, g[N][N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &g[i][j]);
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (g[i][k] && g[k][j])
					g[i][j] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			printf("%3d", g[i][j]);
		puts("");
	}
}
