#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quick_power.h"
 
int main(int argc, char *argv[]) {
  int a, b, p;
 
  while (~scanf("%d%d%d", &a, &b, &p)) {
    printf("%d\n", quick_power(a, b, p));
  }
  return 0;
}