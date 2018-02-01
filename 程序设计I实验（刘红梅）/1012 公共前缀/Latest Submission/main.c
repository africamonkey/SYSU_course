#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
        char * prefix(char* s1, char* s2);
        char *s1;
        char *s2;
        s1 = (char*)malloc(sizeof(char) * 51);
        s2 = (char*)malloc(sizeof(char) * 51);
        scanf("%s", s1);
        scanf("%s", s2);
        char *ans = prefix(s1, s2);
        if (strlen(ans) == 0) {
                printf("no common prefix\n");
        } else {
                printf("%s\n", ans);
        }
        free(ans);
        free(s1);
        free(s2);
        return 0;
}