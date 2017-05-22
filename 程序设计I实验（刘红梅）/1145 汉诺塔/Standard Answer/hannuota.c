#include <stdio.h>

void f(int n, int star, int end, int mid);

int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    f(n, 1, 3, 2);
  }
  return 0;
}

void f(int n, int star, int end, int mid) {
  if (n == 1) {
    printf("move disk %d from peg %d to peg %d\n", n, star, end);
    // cout << "move disk " << n << " from peg " << star << " to peg " << end << endl;
  } else {
    f(n-1, star, mid, end);
    printf("move disk %d from peg %d to peg %d\n", n, star, end);
    // cout << "move disk " << n << " from peg " << star << " to peg " << end << endl;
    f(n-1, mid, end, star);
  }
}                                 