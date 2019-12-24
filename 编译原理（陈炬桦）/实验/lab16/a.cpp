#include <bits/stdc++.h>

#define N 100

using namespace std;

char S, Vn[N], Vt[N], st[N], act1[N][N];
int n, m, mm, k, na, nb, nc, act2[N][N], go[N][N];
pair<char, string> tr[N];
int tr2[N];
string dai[N];
vector<int> stk;

int Vnid(char x) {
	for (int i = 0; i < n; ++i)
		if (Vn[i] == x)
			return i;
	return -1;
}

int Vtid(char x) {
	for (int i = 0; i < m; ++i)
		if (Vt[i] == x)
			return i;
	return -1;
}

void out(int x) {
	for (int i = 0; i < (int)stk.size(); ++i) {
		if (i % 2 == 0)
			printf("%c", char(stk[i]));
		else
			printf("%d", stk[i]);
	}
	printf(" & ");
	printf("%s\n", st + x);
}

int main() {
#ifdef DEBUG
	freopen("a.in", "r", stdin);
#endif
	scanf("%s", st);
	S = st[0];
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", st);
		Vn[i] = st[0];
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		scanf("%s", st);
		Vt[i] = st[0];
	}
	scanf("%d", &mm);
	for (int i = 0; i < mm; ++i) scanf("%*d");
	scanf("%d", &k);
	for (int i = 0; i < k; ++i) {
		int id;
		char x;
		string y;
		scanf("%d", &id);
		scanf("%s", st);
		x = st[0];
		scanf("%s", st);
		y = st;
		tr[i] = make_pair(x, y);
		scanf("%d", &tr2[i]);
	}
	scanf("%d", &mm);
	for (int i = 1; i <= mm; ++i) {
		int x;
		scanf("%d", &x);
		scanf("%s", st);
		dai[i] = st;
	}
	scanf("%d%d%d", &na, &nb, &nc);
	assert(nb == m);
	assert(nc == n - 1);
	for (int i = 0; i < na; ++i) {
		int id;
		scanf("%d", &id);
		for (int j = 0; j < nb; ++j) {
			scanf("%s", st);
			act1[i][j] = st[0];
			scanf("%d", &act2[i][j]);
		}
		for (int j = 0; j < nc; ++j) {
			scanf("%d", &go[i][j]);
		}
	}
	scanf("%s", st);
	int len = strlen(st);
	stk.push_back(int('#'));
	stk.push_back(0);
	int i = 0;
//	out(i);
	while (i < len) {
		while (act1[stk.back()][Vtid(st[i])] == 'r') {
			int Act2 = act2[stk.back()][Vtid(st[i])];
			for (int j = 0; j < (int)tr[Act2].second.length() * 2; ++j)
				stk.pop_back();
			int top = stk.back();
			if (tr2[Act2]) {
				printf(" %s", dai[tr2[Act2]].c_str());
			}
			stk.push_back(int(tr[Act2].first));
			stk.push_back(go[top][Vnid(tr[Act2].first)]);
//			out(i);
		}
		if (act1[stk.back()][Vtid(st[i])] == 'A') {
			break;
		}
		if (act1[stk.back()][Vtid(st[i])] == 's') {
			int Act2 = act2[stk.back()][Vtid(st[i])];
			stk.push_back(int(st[i]));
			stk.push_back(Act2);
			++ i;
//			out(i);
		}
		assert(act1[stk.back()][Vtid(st[i])] != 'k');
	}
	printf(" ");
}
