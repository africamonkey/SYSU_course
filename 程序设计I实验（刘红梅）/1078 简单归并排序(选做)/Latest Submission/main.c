 #include <stdio.h>

#define N 100020

int n, a[N], b[N];

void write() {
  for (int i=1;i<=n;i++)
    	printf("%d%s", a[i], i==n ? "\n" : " ");
}

void work(int *a, int n) {
	if (n == 1) return;
  int mid = (n + 1) / 2;
  work(a, mid);
  work(a + mid, n - mid);
  int lm = mid, rm = n-mid;
  int *l = a, *r = a + mid;
  int i = 1, j = 1, m = 0; 
  while (i <= lm || j <= rm) {
    if (i > lm) {
      b[++m] = r[j];
      j++;
    } else
      if (j > rm) {
        b[++m] = l[i];
        i++;
      } else {
        if (l[i] < r[j])
        	b[++m] = l[i], i++;
        else
          b[++m] = r[j], j++;
      }
  }
  for (int i=1;i<=m;i++) l[i] = b[i];
  write();
}

int main() {
#ifdef DEBUG
	freopen("d.in","r",stdin);
#endif
  scanf("%d", &n);
  if (!n) return 0;
  for (int i=1;i<=n;i++) scanf("%d", &a[i]);
  work(a, n);
}