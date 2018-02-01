#ifndef STACK_H
#define STACK_H
#define STACK_MAX_SIZE 6

int stack_push(int *stack, int num);

int stack_pop(int *stack);

int stack_top(int *stack, int *ret);

int *stack_constructor(void);

void stack_destructor(int *stack);

#endif