#include <stdio.h>
#include "isPrime.h"

void primeList(int n) {
        int i = 2;
        while (n) {
                if (isPrime(i)) {
                        (n != 1) ? printf("%d ", i) : printf("%d", i);
                        n--;
                }
                i++;
        }
        printf("\n");
}
 
int main() {
        int n;
        scanf("%d", &n);
        primeList(n);
}