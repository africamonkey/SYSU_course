#include <stdio.h>
#define N 100020
int main() {
  int n;
  int a[N];
  scanf("%d", &n);
  int top = 0;
  while (n--) {
    int x; scanf("%d", &x);
    if (x>0) a[++top]=x;
  }
  if (top) {
    printf("%d", a[1]);
    for (int i=2;i<=top;i++) printf(" %d", a[i]);
  }
  puts("");
}