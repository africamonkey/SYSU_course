#include <bits/stdc++.h>

#define N 10020

using namespace std;

string s;
vector< string > vn, vt, v[200];
char st[N];

int main() {
	scanf("%s", st);
	s = st;
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", st);
		vn.push_back((string)st);
	}
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", st);
		vt.push_back((string)st);
	}
	scanf("%d", &n);
	while (n--) {
		int x = -1;
		scanf("%s", st);
		for (int i = 0; i < (int)vn.size(); ++i)
			if (vn[i] == (string)st) {
				x = i;
				break;
			}
		scanf("%s", st);
		v[x].push_back(st);
	}
	printf("G[%s]:\n", s.c_str());
	for (int i = 0; i < (int)vn.size(); ++i) {
		printf("%s::=", vn[i].c_str());
		printf("%s", v[i][0].c_str());
		for (int j = 1; j < (int)v[i].size(); ++j)
			printf(" | %s", v[i][j].c_str());
		puts("");
	}
}
