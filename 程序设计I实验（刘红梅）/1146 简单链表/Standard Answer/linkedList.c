#include "linkedList.h"
#include <stdlib.h>

bool insert(int position, int value) {
    if (position < 0 || position > size) 
    	return false;
    node *p, *q;
    if (position == 0) {
        p = (node*)malloc(sizeof(node));
        p->value = value;
        p->next = head;
        head = p;
        size++;
    } else {
        p = head;
        for (int i = 0; i < position-1; ++i) {
            p = p->next;
        }
        q = (node*)malloc(sizeof(node));
        q->value = value;
        q->next = p->next;
        p->next = q;
        size++;
    }
    return true;
}

int get(int position) {
    node* p = head;
    for (int i = 0; i < position; ++i) {
        p = p->next;
    }
    return p->value;
}

void clear() {
    node* p;
    while (head) {
        p = head;
        head = head->next;
        free(p);
    }
    size = 0;
}