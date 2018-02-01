#include <stdio.h>
int main() {
        void myStrcat(char[], int, char[], int);
        char firstStr[101];
        char secondStr[51];
        int firstStrLength = 0, secondStrLength = 0;
        scanf("%s %s", firstStr, secondStr);

        while (firstStr[firstStrLength++]) {}
        while (secondStr[secondStrLength++]) {}
        myStrcat(firstStr, firstStrLength-1, secondStr, secondStrLength-1);

        printf("%s\n", firstStr);

        return 0;
}
