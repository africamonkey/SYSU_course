#include <bits/stdc++.h>

#define N 100020

using namespace std;

char st[N];
vector<string> a;

int main() {
	while (fgets(st, N - 1, stdin) != NULL) {
		stringstream s = stringstream();
		string input;
		s << st;
		a.clear();
		while (s >> input) {
			a.push_back(input);
		}
		if (a.size() != 10) continue;
		if (a[0] == "::1") continue;
		if (a[6] == "/html/JudgeOnline/web/log") continue;
		if (a[6] == "/html/JudgeOnline/web/log1") continue;
		if (a[6] == "/html/JudgeOnline/web/log2") continue;
		if (a[6] == "/html/JudgeOnline/web/log3") continue;
		if (a[6] == "/html/JudgeOnline/web/log4") continue;
		if (a[6] == "/html/JudgeOnline/web/log5") continue;
		if (a[6] == "/html/JudgeOnline/web/log6") continue;
		if (a[6] == "/html/JudgeOnline/web/log7") continue;
		if (a[6] == "/html/JudgeOnline/web/log8") continue;
		if (a[6] == "/html/JudgeOnline/web/log9") continue;
		cout << a[0] << " ";
		string tmp1 = "", tmp2 = "";
		int tt = 0;
		for (int i = 1; i < (int)a[3].length(); ++i) {
			if (tt == 0 && a[3][i] == ':') {
				tt = 1;
				continue;
			}
			if (tt == 0) tmp1 += a[3][i];
			else tmp2 += a[3][i];
		}
		cout << tmp1 << " " << tmp2 << " ";
		cout << a[5].c_str() + 1 << " ";
		tmp1 = "";
		for (int i = 0; i < (int)a[6].length(); ++i) {
			if (a[6][i] == '?') break;
			tmp1 += a[6][i];
		}
		cout << tmp1 << " ";
		cout << a[8] << " " << a[9] << endl;
	}
}
