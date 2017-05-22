#include <stdio.h>

int v[10020];
int n, m;

int main() {
  scanf("%d%d", &n, &m);
  for (int i=0;i<=n;i++) v[i] = 1;
  for (int i=1;i<=m;i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    for (int j=x;j<=y;j++) v[j] = 0;
  }
  int ans = 0;
  for (int i=0;i<=n;i++) ans += v[i];
  printf("%d\n", ans);
}