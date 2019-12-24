#include <bits/stdc++.h>

using namespace std;

struct { int number; string str[10]; } keywords={3,"int","main","return"} ; //关键词
struct { int number; string str[10]; bool in(char x) { for (int i = 0; i < number; ++i) if (str[i][0] == x) return true; return false; } } operators ={5,"+","*","=","+=","*="}; //运算符
struct { int number; string str[10]; bool in(char x) { for (int i = 0; i < number; ++i) if (str[i][0] == x) return true; return false; } } boundaries ={6,"(",")","{","}",",",";"} ; //分界符
struct { int number; string str[100];} identifieres={0}; //标识符
struct { int number; string str[100];} Unsigned_integer={0}; //无符号整数

map<string, pair<int, int> > mp;

int main() {
	for (int i = 0; i < keywords.number; ++i) mp[keywords.str[i]] = make_pair(1, i);
	for (int i = 0; i < operators.number; ++i) mp[operators.str[i]] = make_pair(2, i);
	for (int i = 0; i < boundaries.number; ++i) mp[boundaries.str[i]] = make_pair(3, i);
	for (int i = 0; i < identifieres.number; ++i) mp[identifieres.str[i]] = make_pair(4, i);
	for (int i = 0; i < Unsigned_integer.number; ++i) mp[Unsigned_integer.str[i]] = make_pair(5, i);
	char w = getchar();
	while (1) {
		string str = "";
		while (w <= 32) w = getchar();
		if (w == '#') break;
		pair<int, int> newans;
		if (isalpha(w)) {
			while (isalpha(w) || isdigit(w)) {
				str += w;
				w = getchar();
			}
			newans = make_pair(4, identifieres.number);
		} else if (boundaries.in(w)) {
			str += w;
			w = getchar();
		} else if (operators.in(w)) {
			while (operators.in(w)) {
				str += w;
				w = getchar();
			}
		} else if (isdigit(w)) {
			while (isdigit(w)) {
				str += w;
				w = getchar();
			}
			newans = make_pair(5, Unsigned_integer.number);
		}
		if (mp.find(str) != mp.end()) {
			pair<int, int> ans = mp[str];
			printf("<%d,%d>", ans.first, ans.second);
		} else {
			if (newans.first == 4) identifieres.str[identifieres.number++] = str;
			if (newans.first == 5) Unsigned_integer.str[Unsigned_integer.number++] = str;
			mp[str] = newans;
			printf("<%d,%d>", newans.first, newans.second);
		}
	}
	puts("");
	printf("identifieres:");
	for (int i = 0; i < identifieres.number; ++i) printf("%s%s", identifieres.str[i].c_str(), i == identifieres.number - 1 ? "\n" : " ");
	printf("Unsigned_integer:");
	for (int i = 0; i < Unsigned_integer.number; ++i) printf("%s%s", Unsigned_integer.str[i].c_str(), i == Unsigned_integer.number - 1 ? "\n" : " ");
}
