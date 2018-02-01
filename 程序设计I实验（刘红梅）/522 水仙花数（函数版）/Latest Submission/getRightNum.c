int getRightNum(int n) {
  int ans = -1;
  for (int i=100;i<=n;i++) {
    int a = i%10;
    int b = (i/10)%10;
    int c = (i/100);
    if (a*a*a+b*b*b+c*c*c==i) ans = i;
  }
  return ans;
}