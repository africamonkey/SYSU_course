#include <stdio.h>

#define MAXLENGTH (1000+1)

int main() {
    char s1[MAXLENGTH], s2[101];
    scanf("%s%s", s1, s2);
    int strMatch(const char *, const char *);
    printf("%d\n", strMatch(s1, s2));
    return 0;
}
