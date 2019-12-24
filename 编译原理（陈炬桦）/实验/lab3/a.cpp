#include <bits/stdc++.h>

using namespace std;

string S;
vector<string> Vn;
vector< vector<string> > ans;
vector<string> Vt;
vector< pair<string, string> > t;
bool mp[256];

int main() {
	cin >> S;
	mp[S[0]] = 1;
	int n; cin >> n;
	ans.resize(n);
	for (int i = 1; i <= n; ++i) {
		string x;
		cin >> x;
		Vn.push_back(x);
	}
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		string x;
		cin >> x;
		Vt.push_back(x);
	}
	cin >> n;
	while (n--) {
		string x, y;
		cin >> x >> y;
		if (x == y) {
			printf("delete self production:%s::=%s\n", x.c_str(), y.c_str());
			continue;
		}
		t.push_back(make_pair(x, y));
	}
	int cnt = 1;
	while (cnt) {
		cnt = 0;
		for (int i = 0; i < (int)t.size(); ++i) {
			if (mp[t[i].first[0]]) {
				for (int j = 0; j < (int)t[i].second.length(); ++j)
					if (!mp[t[i].second[j]]) {
						mp[t[i].second[j]] = 1;
						++ cnt;
					}
			}
		}
	}
	for (int i = 0; i < Vn.size(); ++i)
		if (!mp[Vn[i][0]]) {
			printf("unreached Vn:%s\n", Vn[i].c_str());
			for (int j = 0; j < (int)t.size(); ++j)
				if (Vn[i] == t[j].first)
					printf("delete production:%s::=%s\n", t[j].first.c_str(), t[j].second.c_str());
			printf("delete VN:%s\n", Vn[i].c_str());
		}
	for (int i = 0; i < (int)t.size(); ++i) {
		int x = -1;
		for (int j = 0; j < (int)Vn.size(); ++j)
			if (t[i].first == Vn[j]) {
				x = j;
				break;
			}
		ans[x].push_back(t[i].second);
	}
	printf("G[%s]:\n", S.c_str());
	for (int i = 0; i < (int)Vn.size(); ++i)
		if (mp[Vn[i][0]]) {
			printf("%s::=%s", Vn[i].c_str(), ans[i][0].c_str());
			for (int j = 1; j < (int)ans[i].size(); ++j)
				printf(" | %s", ans[i][j].c_str());
			puts("");
		}
}
