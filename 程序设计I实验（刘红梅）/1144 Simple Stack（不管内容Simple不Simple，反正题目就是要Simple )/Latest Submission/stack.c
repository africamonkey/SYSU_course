int stack_push(int *stack, int num) {
  if (stack[0] == 6) return 0;
  stack[++stack[0]] = num;
  return 1;
}

int stack_pop(int *stack) {
  if (stack[0]) {
  	stack[0]--; return 1;
  }
  return 0;
}

int stack_top(int *stack, int *ret) {
  if (stack[0]) {
  	*ret = stack[stack[0]];
    return 1;
  }
  return 0;
}

int *stack_constructor(void) {
  int *s = (int*)malloc(sizeof(int) * 100020);
  s[0] = 0;
  return s;
}

void stack_destructor(int *stack) {
  free(stack);
}