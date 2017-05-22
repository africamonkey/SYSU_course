#include <stdio.h>

int a[100020];

int main() {
	int tot; scanf("%d", &tot);
	while (tot--) {
		int n;
		scanf("%d", &n);
		for (int i=1;i<=n;i++) scanf("%d", &a[i]);
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				if (a[i] > a[j]) {
					int t = a[i]; a[i] = a[j]; a[j] = t;
				}
		for (int i=1;i<=n;i++)
			if (i==1 || a[i] != a[i-1]) {
				printf("%d ", a[i]);
			}
		puts("");
	}
}