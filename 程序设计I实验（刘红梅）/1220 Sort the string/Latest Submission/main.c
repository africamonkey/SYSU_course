 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, id[1020];
char st[1020][102];

int main() {
  scanf("%d", &n);
  for (int i=1;i<=n;i++) scanf("%s", st[i]);
  for (int i=1;i<=n;i++) id[i] = i;
  for (int i=1;i<=n;i++)
    for (int j=i+1;j<=n;j++)
      if (strcmp(st[id[i]], st[id[j]]) > 0) {
        int t = id[i];
        id[i] = id[j];
        id[j] = t;
      }
  for (int i=1;i<=n;i++) puts(st[id[i]]);
}