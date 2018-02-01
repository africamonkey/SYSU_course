#include <stdio.h>
#include "compare.h"
int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    printf("%d\n", compare(a, b, c, d));
}
 