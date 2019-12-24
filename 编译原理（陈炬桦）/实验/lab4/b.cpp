#include <bits/stdc++.h>

#define N 100
#define C 3

using namespace std;

int c, n, m, cnt, S[N], T[N], g[N][N][C];
int ex[N], ey[N], ew[N];
int nS[N], nT[N], mask[N];
char alpha[C];
map<int, int> mp;
queue<int> q;

bool vis(int x) {
	if (mp.find(x) != mp.end()) return 1;
	return 0;
}

int mapv(int x) {
	if (mp.find(x) != mp.end()) return mp[x];
	else {
		for (int i = 0; i < n; ++i)
			if (x >> i & 1) {
				if (S[i]) nS[cnt] = 1;
				if (T[i]) nT[cnt] = 1;
			}
		mask[cnt] = x;
		mp[x] = cnt++;
		return mp[x];
	}
}

int main() {
	scanf("%d", &c);
	for (int i = 0; i < c; ++i) {
		char st[2];
		scanf("%s", st);
		alpha[i] = st[0];
	}
	alpha[c++] = 'k';
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int id;
		scanf("%d%d%d", &id, &S[i], &T[i]);
		assert(i == id);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int x, y, w = -1;
		char st[2];
		scanf("%d%d%s", &x, &y, st);
		for (int j = 0; j < c; ++j)
			if (st[0] == alpha[j]) {
				w = j;
				break;
			}
		g[x][y][w] = 1;
	}
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) {
				if (g[i][k][2] && g[k][j][2]) g[i][j][2] = 1;
				if (g[i][k][2] && g[k][j][0]) g[i][j][0] = 1;
				if (g[i][k][2] && g[k][j][1]) g[i][j][1] = 1;
				if (g[i][k][0] && g[k][j][2]) g[i][j][0] = 1;
				if (g[i][k][1] && g[k][j][2]) g[i][j][1] = 1;
			}
	int start = 0;
	for (int i = 0; i < n; ++i)
		if (S[i])
			start |= 1 << i;
	cnt = 0;
	while (!q.empty()) q.pop();
	q.push(mapv(start));
	int eM = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int a = 0; a < c - 1; ++a) {
			int state = 0;
			for (int xx = 0; xx < n; ++xx)
				if (mask[x] >> xx & 1)
					for (int y = 0; y < n; ++y)
						if (g[xx][y][a]) state |= 1 << y;
			if (state == 0) continue;
			if (!vis(state)) {
				q.push(mapv(state));
			}
			++ eM;
			ex[eM] = x;
			ey[eM] = mapv(state);
			ew[eM] = a;
		}
	}
	puts("Determine State:");
	for (int i = 0; i < cnt; ++i) {
		printf("%d %d %d [", i, nS[i], nT[i]);
		for (int j = 0; j < n; ++j)
			if (mask[i] >> j & 1)
				printf("%d", j);
		printf("]\n");
	}
	puts("Determine Mapping:");
	for (int i = 1; i <= eM; ++i) {
		printf("%d %d %c (%d\n", ex[i], ey[i], alpha[ew[i]], i - 1);
	}
}
