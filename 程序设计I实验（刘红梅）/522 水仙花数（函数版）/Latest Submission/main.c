#include <stdio.h>
#include "getRightNum.h"

int main(void) {
    int num;
    scanf("%d", &num);
    int after = getRightNum(num);
    if(after == -1)
        printf("Doesn't exist\n");
    else 
        printf("%d\n", after);
    return 0;
}