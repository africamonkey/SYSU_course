#include <bits/stdc++.h>

using namespace std;

int v[256];
char st[200020];

int main() {
	scanf("%s", st);
	for (int i = 0; st[i]; ++i)
		v[st[i]] = 1;
	for (int i = 0; i < 256; ++i)
		if (v[i])
			putchar(i);
	puts("");
}
