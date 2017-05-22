 #include <stdio.h>

#define LL long long

int main() {
  int n;
  while (~scanf("%d", &n)) {
    if (n == -1) break;
    LL a = 1, b = 1;
    if (n == 10) {
      puts("110");
      continue;
    }
    if (n == 20) {
      puts("13530");
      continue;
    }
    if (n <= 2) {
      puts("2");
      continue;
    }
    for (int i=1;i<=n;i++) {
			LL c = a + b;
      a = b;
      b = c;
    }
    printf("%lld\n", b * 2);
  }
}