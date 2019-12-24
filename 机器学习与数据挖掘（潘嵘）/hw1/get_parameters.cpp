#include <bits/stdc++.h>

#define N 100020

using namespace std;

vector<string> a[256];
char st[N], s[N];

int main() {
	FILE *fin = fopen("combined.csv", "r");
	FILE *fout = fopen("parameters.txt", "w");
	while (fgets(st, N, fin)) {
		int len = strlen(st);
		st[len - 1] = ',';
		st[len] = 0;
		int cnt = 0;
		int t = 0;
		for (int i = 0; i < len; ++i) {
			s[t++] = st[i];
			if (st[i] == ',') {
				s[t] = 0;
				a[cnt++].push_back((string)s);
				t = 0;
			}
		}
	}
	for (int i = 0; i < 256; ++i) {
		sort(a[i].begin(), a[i].end());
		a[i].erase(unique(a[i].begin(), a[i].end()), a[i].end());
		for (int j = 0; j < (int)a[i].size(); ++j)
			fprintf(fout, "%s", a[i][j].c_str());
		fprintf(fout, "\n");
	}
}
