long long getStepNum(int n) {
  long long ret = 0;
  for (int i=1;i<=n;i++) ret = (ret * 2 + 1) % 10007;
  ret *=3;
  ret %= 10007;
  return ret;
}