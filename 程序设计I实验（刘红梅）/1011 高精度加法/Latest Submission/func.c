
void swap(short *a, short *b) {
  short t; t = *a; *a = *b; *b = t;
}
short * plus(short *a, short *b) {
   int n = 0, m = 0;
   while (~a[n]) n++;
   while (~b[m]) m++;
   short *c = (short*)malloc(sizeof(short) * 101);
   for (int i=0;i<101;i++) c[i] = 0;
   for (int i=0;i<n/2;i++) swap(&a[i], &a[n-1-i]);
   for (int i=0;i<m/2;i++) swap(&b[i], &b[m-1-i]);
   for (int i=n;i<101;i++) a[i] = 0;
   for (int i=m;i<101;i++) b[i] = 0;
   int n1 = n, m1 = m;
   if (m > n) n = m;
   for (int i=0;i<n;i++) c[i] = a[i] + b[i];
   for (int i=0;i<n;i++) c[i+1] += c[i] / 10, c[i] %= 10;
   if (c[n]) n++;
   c[n] = -1;
   for (int i=0;i<n1/2;i++) swap(&a[i], &a[n1-1-i]);
   for (int i=0;i<m1/2;i++) swap(&b[i], &b[m1-1-i]);
   a[n1] = -1; b[m1] = -1;
   for (int i=0;i<n/2;i++) swap(&c[i], &c[n-1-i]);
   return c;
 }