#include <stdio.h>
#define N 100020
int prime[N],mu[N],phi[N],v[N],top;
int main() {
mu[1]=phi[1]=1;top=0;
for (int i=2;i<N;i++) {
	if (!v[i]) prime[++top]=i, mu[i] = -1, phi[i] = i-1;
	for (int j=1;i*prime[j]<N && j<=top;j++) {
		v[i*prime[j]] = 1;
		if (i%prime[j]) {
			mu[i*prime[j]] = -mu[i];
			phi[i*prime[j]] = phi[i] * (prime[j]-1);
		} else {
			mu[i*prime[j]] = 0;
			phi[i*prime[j]] = phi[i] * prime[j];
			break;
		}
	}
}
  int n;
  scanf("%d",&n);
  for (int i=1;i<=n;i++) printf("%d%s",prime[i],i==n?"\n":" ");
}