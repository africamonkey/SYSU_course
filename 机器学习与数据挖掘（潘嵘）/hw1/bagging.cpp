#include <bits/stdc++.h>

#define N 19226

using namespace std;

vector<double> a[N];

void read(int i) {
	char st[100];
	sprintf(st, "./remote_output/out%d.csv", i);
	FILE *f = fopen(st, "r");
	fscanf(f, "%*s");
	for (int i = 0; i < N; ++i) {
		int x;
		double y;
		fscanf(f, "%d,%lf", &x, &y);
		a[i].push_back(y);
	}
}

int main() {
	for (int i = 99; i < 10000; i += 100) {
		read(i);
	}
	freopen("bagging_out.csv", "w", stdout);
	puts("Id,label");
	for (int i = 0; i < N; ++i) {
		sort(a[i].begin(), a[i].end());
		double avg = 0;
		for (int j = 0; j < (int)a[i].size(); ++j) avg += a[i][j];
		avg /= a[i].size();
		double mid = a[i][(int)a[i].size() / 2];
		printf("%d,%.20lf\n", i, mid);
	}
}
