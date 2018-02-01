int compare(const int a, const int b, const int c, const int d) {
  if (a*d<c*b) return -1;
  if (a*d==c*b) return 0;
  return 1;
}