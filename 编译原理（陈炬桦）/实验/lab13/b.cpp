#include <bits/stdc++.h>

#define N 100

using namespace std;

char S, Vn[N], Vt[N], st[N];
int n, m, k;

int main() {
#ifdef DEBUG
	freopen("b.in", "r", stdin);
#endif
	scanf("%s", st);
	S = st[0];
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", st);
		Vn[i] = st[0];
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%s", st);
		Vt[i] = st[0];
	}	
	scanf("%d", &k);
	int top = 0;
	for (int i = 1; i <= k; ++i) {
		int id;
		scanf("%d", &id);
		char x;
		scanf("%s", st);
		x = st[0];
		string y;
		scanf("%s", st);
		y = st;
		for (int j = 0; j <= (int)y.length(); ++j) {
			printf("%3d%3d%3d%3c   %s\n", ++top, i, j, x, y.c_str());
		}
	}
}
