#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

Node *createNode(int data, Node *next) {
  Node *ret = (Node *)malloc(sizeof(Node));
  if (!ret) exit(1);
  ret->data = data;
  ret->next = next;
  return ret;
}

void freeStackElem(Stack *stack) {
  while (size(stack) != 0) {
    pop(stack);
  }
}

int main() {
  Stack s1 = {0, NULL}, s2 = {0, NULL};
  int rand = 0;
  scanf("%d", &rand);
  for (int i = 0; i < rand; ++i) {
    push(i % 2 ? &s1 : &s2, i);
  }
  for (int i = 0; i < rand; ++i) {
    push(i % 2 ? &s2 : &s1, i);    
  }
  printf("The top of Stack 1 is: %d\n", top(&s1));
  printf("The top of Stack 2 is: %d\n", top(&s2));
  puts("Now pop from Stack 1: ");
  while (!empty(&s1)) {
    printf("%d ", top(&s1));
    pop(&s1);
    if (size(&s1) % 5) pop(&s2);
  }
  printf("\nNow Stack 1 is empty ? %s\n", empty(&s1) ? "yes" : "no");
  printf("Size of Stack 2: %d\n", size(&s2));
  freeStackElem(&s2);
  printf("Empty Stack2: %s\n", empty(&s2) ? "success" : "no");
  freeStackElem(&s1);
}