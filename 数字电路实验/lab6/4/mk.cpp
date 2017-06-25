#include <bits/stdc++.h>

using namespace std;

int cc1[64], cc2[64], cnt;

int main() {
	cnt = 0;
	for (int a = 0; a < 2; ++a)
		for (int b = 0; b < 2; ++b)
			for (int c = 0; c < 2; ++c) 
				for (int d = 0; d < 2; ++d)
					for (int e = 0; e < 2; ++e)
						for (int f = 0; f < 2; ++f) {
							int g = d * 4 + e * 2 + f;
							switch (g) {
								case 0: cc1[cnt] = c & b; break;
								case 1: cc1[cnt] = c | b; break;
								case 2: cc1[cnt] = !c; break;
								case 3: cc1[cnt] = !b; break;
								case 4: cc1[cnt] = c ^ b; break;
								case 5: cc1[cnt] = c ^ b ^ a; cc2[cnt] = ((c & b) | (c & a) | (b & a)); break;
								case 6: cc1[cnt] = c ^ b ^ a; cc2[cnt] = ((!c & b) | (!c & a) | (b & a)); break;
								case 7: cc1[cnt] = 0; break;
							}
							++cnt;
						}
	for (int i = 0; i < cnt; ++i)
		printf("%d", cc1[i]);
	puts("");
	for (int i = 0; i < cnt; ++i)
		printf("%d", cc2[i]);
	puts("");
}
