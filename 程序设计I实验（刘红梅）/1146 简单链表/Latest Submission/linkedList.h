#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdbool.h>

typedef struct node {
	int value;
	struct node* next;
} node ;

int size; // the size of linked list
node* head; // the head of linkedlist

//insert the value to the right position
//if the position is not valid, return false
//if insert successfully, return true
bool insert(int position, int value);

// return the value in the given position
int get(int position);

//clear the linkedlist, remember to free the memory you allocated
void clear();

#endif