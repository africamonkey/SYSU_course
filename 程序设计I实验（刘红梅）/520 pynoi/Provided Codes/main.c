#include <stdio.h>
#include "getStepNum.h"
int main() {
    int n;
    scanf("%d", &n);
    long long answer = getStepNum(n);
    printf("%lld\n", answer);
    return 0;
}