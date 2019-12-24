#include <bits/stdc++.h>

#define N 20

using namespace std;

int n, n1, n2, n3, ans[N][N];
char st[N], c[N], tr[N], S[N], SS;
map<string, char> mp;
map<string, int> mp2;
string tttt[N];

int get(char x) {
	for (int i = 1; i <= n; ++i)
		if (c[i] == x)
			return i;
	return 0;
}

int isVt(char x) {
	return n1 < get(x) && get(x) <= n;
}

int main() {
#ifdef DEBUG
	freopen("a.in", "r", stdin);
#endif
	scanf("%s", st);
	SS = st[0];
	n1 = 0, n2 = 0, n3 = 0;
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
	scanf("%d", &n3);
	for (int i = 1; i <= n3; ++i) scanf("%*d");
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
		mp[string(st)] = xx;
		int yy;
		scanf("%d", &yy);
		mp2[string(st)] = yy;
	}
	int ttt;
	scanf("%d", &ttt);
	for (int i = 1; i <= ttt; ++i) {
		int id;
		scanf("%d", &id);
		scanf("%s", st);
		tttt[i] = st;
	}
	scanf("%d", &m);
	assert(m == n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &ans[i][j]);
	c[++n] = '#';
	for (int i = 1; i <= n1 + n2; ++i) ans[i][n] = 3, ans[n][i] = 1;
	scanf("%s", tr + 1);
//	printf("# & %s\n", tr + 1);
	S[1] = '#';
	int i = 1, j = 1;
	while (1) {
		if (ans[get(S[i])][get(tr[j])] == 0) {
			puts("error");
			exit(0);
		}
		if (ans[get(S[i])][get(tr[j])] == 3) {
			int k = i;
			while (ans[get(S[k - 1])][get(S[k])] != 1) -- k;
			string tt = "";
			for (int ll = k; ll <= i; ++ll)
				tt += S[ll];
			if (mp[tt]) {
				i = k;
				S[i] = mp[tt];
				S[i + 1] = 0;
				int test = mp2[tt];
				if (test) {
					printf(" %s", tttt[test].c_str());
				}
//				printf("%s & %s\n", S + 1, tr + j);
				if (i == 2 && S[1] == '#' && S[2] == SS && tr[j] == '#') {
					// OK
					puts("");
					exit(0);
				}
			} else {
				if (i == 2 && S[1] == '#' && S[2] == SS && tr[j] == '#') {
					// OK
					puts("");
					exit(0);
				} else {
					puts("error");
					exit(0);
				}
			}
		} else {
			i = i + 1;
			S[i] = tr[j];
			S[i + 1] = 0;
			j = j + 1;
//			printf("%s & %s\n", S + 1, tr + j);
			if (i == 2 && S[1] == '#' && S[2] == SS && tr[j] == '#') {
				// OK
				puts("");
				exit(0);
			}
		}
	}
}
