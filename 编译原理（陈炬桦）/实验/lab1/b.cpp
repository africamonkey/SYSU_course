#include <bits/stdc++.h>

using namespace std;

struct Node {
	int son[256];
	int terminal;
} node[200020];
int n, v[256];
char st[200020];

int main() {
	int first = 1;
	int top = 1;
	scanf("%d", &n);
	for (int t = 1; t <= n; ++t) {
		scanf("%s", st);
		memset(v, 0, sizeof(v));
		for (int i = 0; st[i]; ++i)
			v[st[i]] = 1;
		int x = 1;
		for (int i = 0; i < 256; ++i)
			if (v[i]) {
				if (!node[x].son[i]) node[x].son[i] = ++top;
				x = node[x].son[i];
			}
		if (!node[x].terminal) {
			if (first) first = 0;
			else puts("");
			for (int i = 0; i < 256; ++i)
				if (v[i])
					putchar(i);
			node[x].terminal = 1;
		}
	}
}
