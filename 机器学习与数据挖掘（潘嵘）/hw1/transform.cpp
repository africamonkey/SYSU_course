#include <bits/stdc++.h>

#define N 10000020
#define M 131072
#define K 249

using namespace std;

string excel[M][K];
char st[N], s[N];
bool ok[K], alpha[K];
vector<string> v[K];
double lmin[K], lmax[K], la[M][K];

int main() {
	FILE *fparameters = fopen("parameters.txt", "r");
	for (int i = 0; i < K; ++i) {
		fgets(st, N, fparameters);
		ok[i] = 1;
		// ok[i] = st[0] != ',';
		int len = strlen(st);
		st[--len] = 0;
		for (int j = 0; j < len; ++j)
			if (!isalpha(st[j]) && !isdigit(st[j]) && st[j] != ',' && st[j] != '.')
				ok[i] = 0;
		for (int j = 0; j < len; ++j)
			if (isalpha(st[j]))
				alpha[i] = 1;
		int t = 0;
		for (int j = 0; j < len; ++j) {
			if (st[j] != ',') s[t++] = st[j];
			else {
				s[t] = 0;
				v[i].push_back((string)s);
				t = 0;
			}
		}
	}
	fclose(fparameters);
	int n = 0;
	while (fgets(st, N, stdin)) {
		int len = strlen(st);
		st[len - 1] = ',';
		st[len] = 0;
		int cnt = 0;
		int t = 0;
		for (int i = 0; i < len; ++i) {
			if (st[i] != ',') s[t++] = st[i];
			else {
				s[t] = 0;
				excel[n][cnt++] = (string)s;
				t = 0;
			}
		}
		++ n;
	}
	for (int j = 0; j < K; ++j) {
		if (alpha[j] || (int)v[j].size() < 10) {
			for (int i = 0; i < n; ++i) {
				int x = lower_bound(v[j].begin(), v[j].end(), excel[i][j]) - v[j].begin() + 1;
				sprintf(s, "%d", x);
				excel[i][j] = (string)s;
			}
			for (int i = 0; i < (int)v[j].size(); ++i) {
				char sss[100];
				sprintf(sss, "%d", i + 1);
				v[j][i] = (string)sss;
			}
		} else {
			for (int i = 0; i < (int)v[j].size(); ++i)
				if (v[j][i] == (string)"")
					v[j][i] = "0";
		}
		if (v[j].size() == 1) ok[j] = 0;
	}
	for (int i = 0; i < K; ++i) {
		lmin[i] = 1e100;
		lmax[i] = -1e100;
		for (int j = 0; j < (int)v[i].size(); ++j) {
			double x;
			sscanf(v[i][j].c_str(), "%lf", &x);
			lmin[i] = min(lmin[i], x);
			lmax[i] = max(lmax[i], x);
		}
	}
	for (int i = 0; i < n; ++i)
		for (int j = 1; j < K; ++j)
			if (ok[j]) {
				sscanf(excel[i][j].c_str(), "%lf", &la[i][j]);
			}
	for (int i = 0; i < n; ++i) {
		int t = 0;
		for (int kk = 0; kk < (int)excel[i][0].size(); ++kk)
			s[t++] = excel[i][0][kk];
		s[t++] = ',';
		for (int j = 1; j < K; ++j)
			if (ok[j]) {
				char sss[100];
				la[i][j] = (la[i][j] - lmin[j]) / (lmax[j] - lmin[j]);
				sprintf(sss, "%.10lf", la[i][j]);
				int len = strlen(sss);
				for (int kk = 0; kk < len; ++kk)
					s[t++] = sss[kk];
//				for (int kk = 0; kk < (int)excel[i][j].size(); ++kk)
//					s[t++] = excel[i][j][kk];
				s[t++] = ',';
			}
		s[--t] = 0;
		puts(s);
	}

}
