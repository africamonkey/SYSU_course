#include "stack.h"
#include <stdlib.h>
#include <string.h>

int *stack_constructor(void) {
  size_t stack_size = (STACK_MAX_SIZE + 1) * sizeof(1);
  int *ret = (int *)malloc(stack_size);
  if (ret == NULL) {
    exit(1);
  }
  memset(ret, 0, stack_size);
  return ret;
}

void stack_destructor(int *stack) {
  if (stack != NULL) free(stack);
}

int stack_push(int *stack, int num) {
  if (stack[0] >= STACK_MAX_SIZE) return 0;
  stack[++stack[0]] = num;
  return 1;
}

int stack_pop(int *stack) {
  if (stack[0] <= 0) return 0;
  --stack[0];
  return 1;
}

int stack_top(int *stack, int *ret) {
  if (stack[0] <= 0) return 0;
  *ret = stack[stack[0]];
  return 1;
}
