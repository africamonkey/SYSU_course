 #include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void pop(Stack *s) {
  Node *a = s->top;
  s->top = a->next;
  free(a);
  s->size --;
}
int top(Stack *s) {
  return (s->top)->data;
}
void push(Stack *s, int a) {
  Node *b = createNode(a, s->top);
  s->top = b;
  (s->size) ++;
}
int size(Stack *s) {
  return s->size;
}
int empty(Stack *s) {
  return size(s) == 0;
}
