#include <stdio.h>
#include "stack.h"

#define str(a) #a
#define pushFormat "push %d into %s: %s\n"

int main() {
  int *stack_1 = stack_constructor();
  int *stack_2 = stack_constructor();
  int times = 0, temp = 0;
  scanf("%d", &times);
  for (int i = 0; i < times; ++i) {
    scanf("%d", &temp);
    printf(pushFormat, temp, str(stack_1),
           stack_push(stack_1, temp) ? str(success) : str(failed));
  }
  scanf("%d", &times);
  for (int i = 0; i < times; ++i) {
    int num = 0;
    int flag = stack_top(stack_1, &num);
    printf("get the top from stack_1: %s\n", flag ? str(success) : str(failed));
    if (flag) {
      printf("The top: %d\n", num);
      stack_pop(stack_1);
    } else {
      puts("The top: None");
    }
    flag = stack_push(stack_2, num);
    printf(pushFormat, num, str(stack_2), flag ? str(success) : str(failed));
    flag = stack_push(stack_2, num + 1);
    printf(pushFormat, num + 1, str(stack_2), flag ? str(success) : str(failed));
  }

  int num = 0;
  printf("The num in stack_1:");
  while (stack_top(stack_1, &num)) {
    printf(" %d", num);
    stack_pop(stack_1);
  }
  printf("\nThe num in stack_2:");
  while (stack_top(stack_2, &num)) {
    printf(" %d", num);
    stack_pop(stack_2);
  }
  putchar('\n');
  stack_destructor(stack_1);
  stack_destructor(stack_2);
  return 0;
}