 #include <stdio.h>
#include <string.h>
#define N 1020
char s1[N], s2[N];
int v[255];
int n, m;
int main() {
	scanf("%s%s", s1, s2);
  n = strlen(s1); m = strlen(s2);
  if (n != m) {
    puts("NO");
    return 0;
  }
  memset(v, 0, sizeof(v));
  for (int i=0;i<n;i++) v[s1[i]] ++;
  for (int i=0;i<n;i++) v[s2[i]] --;
  for (int i=0;i<255;i++)
    	if (v[i]) {
        puts("NO");
        return 0;
      }
  puts("YES");
  return 0;
}