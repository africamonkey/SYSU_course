#include <bits/stdc++.h>

using namespace std;

char S;
vector<char> Vn, Vt;
vector<char> first[256];
vector<string> trans[256];
bool v[256];
char st[100];
int n, m, k;

bool find_k(char x) {
	for (int i = 0; i < (int)first[x].size(); ++i)
		if (first[x][i] == 'k')
			return true;
	return false;
}

void First(char x) {
	if (v[x]) return; v[x] = 1;
	if (x == 'k') {
		first[x].clear();
		first[x].push_back(x);
		return;
	}
	for (int i = 0; i < m; ++i)
		if (Vt[i] == x) {
			first[x].clear();
			first[x].push_back(x);
			return;
		}
	int id = -1;
	for (int i = 0; i < n; ++i)
		if (Vn[i] == x) {
			id = i;
			break;
		}
	assert(id != -1);
	for (int i = 0; i < (int)trans[id].size(); ++i) {
		string dest = trans[id][i];
		for (int j = 0; j < (int)dest.length(); ++j) {
			First(dest[j]);
			for (int kk = 0; kk < (int)first[dest[j]].size(); ++kk)
				if (first[dest[j]][kk] != 'k')
					first[x].push_back(first[dest[j]][kk]);
			if (!find_k(dest[j])) break;
			if (j == (int)dest.length() - 1)
				first[x].push_back('k');
		}
		sort(first[x].begin(), first[x].end());
		first[x].erase(unique(first[x].begin(), first[x].end()), first[x].end());
	}
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
		Vn.push_back(st[0]);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		scanf("%s", st);
		Vt.push_back(st[0]);
	}

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
		for (int j = 0; j < n; ++j)
			if (Vn[j] == x) {
				trans[j].push_back(y);
				break;
			}
	}
	for (int i = 0; i < n; ++i)
		First(Vn[i]);
	printf("FIRST(VT)\r\n");
	for (int i = 0; i < n; ++i) {
		char x = Vn[i];
		memset(v, 0, sizeof(v));
		for (int j = 0; j < (int)first[x].size(); ++j)
			v[first[x][j]] = 1;
		first[x].clear();
		for (int j = 0; j < (int)Vt.size(); ++j)
			if (v[Vt[j]])
				first[x].push_back(Vt[j]);
		if (v['k']) first[x].push_back('k');
		printf("%c ", x);
		for (int j = 0 ; j < (int)first[x].size(); ++j)
			printf("%c", first[x][j]);
		printf("\r\n");
	}
}
