#include<stdio.h>
#include<stdlib.h>
int main() {
        int RecursionLength(char *s);
        int NoRecursionLength(char *s);
        char *s;
        s = (char*)malloc(sizeof(char*) * 60);
        scanf("%s", s);
        printf("with recursion: %d\n", RecursionLength(s));
        printf("without recursion: %d\n", NoRecursionLength(s));
        free(s);
        return 0;
}
