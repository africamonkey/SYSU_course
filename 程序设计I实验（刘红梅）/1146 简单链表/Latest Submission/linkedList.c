 #include "linkedList.h"

bool insert(int position, int value) {
  if (!position) {
    node *x = head;
    head = (node*)malloc(sizeof(node));
    (*head).value = value;
    (*head).next = x;
    ++size;
    return true;
  }
  node *x = head, *y = 0;
  for (int i=0;i<position;i++) {
    y = x;
    if (!y) break;
    x = (*x).next;
  }
  if (!y) return false;
  node *z = (node*)malloc(sizeof(node));
  (*y).next = z;
  (*z).value = value;
  (*z).next = x;
  ++size;
  return true;
}

int get(int position) {
  node *x = head;
  for (int i=0;i<position;i++) {
    if (!x) break;
    x = (*x).next;
  }
  return (*x).value;
}

void clear() {
  for (node *x = head; x; ) {
    node *y = (*x).next;
    free(x);
    x = y;
  }
}



