 #include <string.h>

int strMatch(const char *a, const char *b) {
  char * c = strstr(a, b);
  if (c == 0) return -1;
  return c - a;
}