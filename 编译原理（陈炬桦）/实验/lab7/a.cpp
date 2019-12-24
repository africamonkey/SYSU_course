#include <bits/stdc++.h>

#define N 102

using namespace std;

int n, m, k;
char S, s[N], t[N];
pair<char, string> p[N];
char tmp[N];
int mps[256], mpt[256];
string ans[N][N];

int main() {
	scanf("%s", tmp);
	S = tmp[0];
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", tmp);
		s[i] = tmp[0];
		mps[s[i]] = i;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%s", tmp);
		t[i] = tmp[0];
		mpt[t[i]] = i;
	}
	++ m;
	t[m] = '#';
	mpt['#'] = m;
	scanf("%d", &k);
	for (int i = 1; i <= k; ++i) {
		int x;
		scanf("%d", &x);
		scanf("%s", tmp);
		scanf("%s", tmp + 1);
		p[x] = make_pair(tmp[0], (string)(tmp + 1));
	}
	scanf("%d", &k);
	for (int i = 1; i <= k; ++i) {
		int x;
		scanf("%d", &x);
		scanf("%s", tmp);
		scanf("%s", tmp + 1);
		scanf("%d", &x);
		ans[ mps[tmp[0]] ][ mpt[tmp[1]] ] = p[x].second;
	}
	printf("%5s", "");
	for (int j = 1; j <= m; ++j) printf("%5c", t[j]);
	puts("");
	for (int i = 1; i <= n; ++i) {
		printf("%5c", s[i]);
		for (int j = 1; j <= m; ++j) {
			printf("%5s", ans[i][j].c_str());
		}
		puts("");
	}
}
