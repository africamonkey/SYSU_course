#include <string.h>
int NoRecursionLength(char *s) {
  return strlen(s);
}

int RecursionLength(char *s) {
  return NoRecursionLength(s);
}