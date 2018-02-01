#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAXl (100+1)
 
int main() {
    short s1[MAXl], s2[MAXl];
    int l1, l2, i;
    scanf("%d", &l1);
    for (i = 0; i < l1; ++i)
        scanf("%hd", s1+i);
    scanf("%d", &l2);
    for (i = 0; i < l2; ++i)
        scanf("%hd", s2+i);
    s1[l1] = s2[l2] = -1;
    short *plus(short *, short *);
    short *ans = plus(s1, s2);
    for (i = 0; s1[i] >= 0; ++i)
        printf("%hd", s1[i]);
    printf("\n");
    for (i = 0; s2[i] >= 0; ++i)
        printf("%hd", s2[i]);
    printf("\n");
    for (i = 0; ans[i] >= 0; ++i)
        printf("%hd", ans[i]);
    printf("\n");
    free(ans);
    return 0;
}