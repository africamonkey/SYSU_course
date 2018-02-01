#ifndef STACK_H
#define STACK_H

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct Stack {
  int size;
  Node *top;
} Stack;


Node *createNode(int data, Node *next);

void pop(Stack *);
int top(Stack *);
void push(Stack *, int);
int size(Stack *);
int empty(Stack *);

void freeStackElem(Stack *);

#endif