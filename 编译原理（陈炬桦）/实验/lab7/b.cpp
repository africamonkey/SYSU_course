#include <bits/stdc++.h>

#define N 102

using namespace std;

int n, m, k;
char S, s[N], t[N];
pair<char, string> p[N];
char tmp[N];
int mps[256], mpt[256];
string ans[N][N];
vector<char> stk;

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
	scanf("%s", tmp);
	stk.push_back('#');
	stk.push_back(S);
	int len = strlen(tmp);
	for (int i = 0; i <= len; ++i) {
		int first = 1;
		do {
			putchar('#');
			for (int j = 0; j < i - first; ++j) putchar(tmp[j]);
			printf(" & ");
			for (int j = (int)stk.size() - 1; j >= 0; --j) putchar(stk[j]);
			puts("");
			first = 0;
			int x = mps[stk.back()];
			stk.pop_back();
			int y = mpt[tmp[i]];
			for (int j = (int)ans[x][y].size() - 1; j >= 0; --j) 
				if (ans[x][y][j] != 'k')
					stk.push_back(ans[x][y][j]);
		} while (stk[stk.size() - 1] != tmp[i]);
	}
	
}
