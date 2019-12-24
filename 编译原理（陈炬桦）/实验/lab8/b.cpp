#include <bits/stdc++.h>

using namespace std;

char S;
vector<char> Vn, Vt;
char st[100];
vector< pair<char, string> > pro;
vector< string > hi[256];
int n, m, k, v[256];

void dfs(char x) {
	if (v[x]) return; v[x] = 1;
	for (int i = 0; i < (int)Vt.size(); ++i)
		if (Vt[i] == x)
			return;
	for (int i = 0; i < (int)pro.size(); ++i)
		if (pro[i].first == x) {
			for (int j = 0; j < (int)pro[i].second.length(); ++j) 
				dfs(pro[i].second[j]);
		}
}

void dfs2(char x) {
	if (v[x]) return; v[x] = 1;
	for (int i = 0; i < (int)Vt.size(); ++i)
		if (Vt[i] == x) {
			v[x] = 2;
			return;
		}
	for (int i = 0; i < (int)pro.size(); ++i)
		if (pro[i].first == x) {
			for (int j = 0; j < (int)pro[i].second.length(); ++j) {
				dfs2(pro[i].second[j]);
				if (v[pro[i].second[j]] == 2) v[x] = 2;
			}
		}
}

void del(char x) {
	printf("delete VN:%c\n", x);
	for (int j = 0; j < (int)pro.size(); ++j) {
		int ok = 0;
		for (int kk = 0; kk < (int)pro[j].second.length(); ++kk)
			if (pro[j].second[kk] == x) {
				ok = 1;
				break;
			}
		if (pro[j].first == x) ok = 1;
		if (ok) {
			printf("delete production:%c::=%s\n", pro[j].first, pro[j].second.c_str());
			pro.erase(pro.begin() + j);
			-- j;
		}
	}
}

int main() {
#ifdef DEBUG
	freopen("b.in", "r", stdin);
#endif
	scanf("%s", st);
	S = st[0];
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", st);
		Vn.push_back(st[0]);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		scanf("%s", st);
		Vt.push_back(st[0]);
	}
	scanf("%d", &k);
	for (int i = 0; i < k; ++i) {
		char x;
		string y;
		scanf("%s", st);
		x = st[0];
		scanf("%s", st);
		y = st;
		if (y.length() == 1 && y[0] == x) {
			printf("delete self production:%c::=%s\n", x, y.c_str());
		} else {
			pro.push_back(make_pair(x, y));
		}
	}
	int change = 1;
	while (change) {
		change = 0;
		memset(v, 0, sizeof(v));
		dfs(S);
		for (int i = 0; i < (int)Vn.size(); ++i)
			if (!v[Vn[i]]) {
				printf("unreached Vn:%c\n", Vn[i]);
				del(Vn[i]);
				change = 1;
				Vn.erase(Vn.begin() + i);
				break;
			}
		if (change) continue;
		memset(v, 0, sizeof(v));
		dfs2(S);
		for (int i = (int)Vn.size() - 1; i >= 0; --i) {
			assert(v[Vn[i]]);
			if (v[Vn[i]] == 1) {
				printf("unusefulNv:%c\n", Vn[i]);
				del(Vn[i]);
				change = 1;
				Vn.erase(Vn.begin() + i);
				break;
			}
		}
	}
	printf("G[%c]:\n", S);
	for (int i = 0; i < (int)pro.size(); ++i) {
		hi[pro[i].first].push_back(pro[i].second);
	}
	for (int i = 0; i < (int)Vn.size(); ++i) {
		if (hi[Vn[i]].empty()) continue;
		printf("%c::=%s", Vn[i], hi[Vn[i]][0].c_str());
		for (int j = 1; j < (int)hi[Vn[i]].size(); ++j)
			printf(" | %s", hi[Vn[i]][j].c_str());
		puts("");
	}
}
