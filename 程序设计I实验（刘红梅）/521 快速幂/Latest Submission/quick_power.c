int quick_power(int base, int times, int mod) {
  int ret = 1;
  while (times) {
    if (times&1) ret=(long long)ret*base % mod;
    base=(long long)base*base%mod;
    times>>=1;
  }
  return ret;
}
