#include <bits/stdc++.h>

#define N 100

using namespace std;

char S, Vn[N], Vt[N], st[N];
int n, m, k, hhh[256][256];
string trans[N], huan[N];
stack<char> stk;

int main() {
#ifdef DEBUG
	freopen("a.in", "r", stdin);
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
	int xxx; scanf("%d", &xxx);
	for (int i = 1; i <= xxx; ++i) scanf("%*d");
	scanf("%d", &k);
	for (int i = 1; i <= k; ++i) {
		int id;
		char x;
		string y;
		scanf("%d", &id);
		scanf("%s", st);
		x = st[0];
		scanf("%s", st);
		y = st;
		if (y == "k") huan[id] = "";
		else huan[id] = y;
	}
	scanf("%d", &xxx);
	for (int i = 1; i <= xxx; ++i) {
		int id;
		scanf("%d", &id);
		scanf("%s", st);
		trans[i] = st;
	}
	scanf("%d", &xxx);
	for (int i = 1; i <= xxx; ++i) {
		int id;
		scanf("%d", &id);
		scanf("%s", st);
		char x = st[0];
		scanf("%s", st);
		char y = st[0];
		scanf("%d", &id);
		hhh[x][y] = id;
	}
	scanf("%s", st);
	stk.push('#');
	stk.push('E');
	int i = 0, len = strlen(st);
	while (!stk.empty()) {
		if (stk.top() == '#') {
			if (st[i] == '#') {
				break;
			}
			assert(0);
		}
		if (isdigit(stk.top())) {
			printf(" %s", trans[stk.top() - '0'].c_str());
			stk.pop();
			continue;
		}
		bool check = false;
		for (int j = 1; j <= m; ++j)
			if (stk.top() == Vt[j]) {
				check = true;
				break;
			}
		if (check) {
			if (stk.top() == st[i]) {
				stk.pop();
				++ i;
				continue;
			} else {
				assert(0);
			}
		} else {
			if (hhh[stk.top()][st[i]] == 0) assert(0);
			int biao = hhh[stk.top()][st[i]];
			stk.pop();
			for (int i = (int)huan[biao].size() - 1; i >= 0; --i)
				stk.push(huan[biao][i]);
			continue;
		}
	}
	puts("");
}
