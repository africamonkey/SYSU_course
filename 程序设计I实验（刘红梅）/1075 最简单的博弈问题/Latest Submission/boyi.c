 #include <stdio.h>

int main() {
  int tot;
  scanf("%d", &tot);
  while (tot--) {
    int x;
    scanf("%d", &x);
    puts(x % 3 ? "dalao win!": "xinpang win!");
  }
}