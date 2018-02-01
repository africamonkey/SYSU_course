#include <stdio.h>
int main() {
int n,max=-2147483648,min=2147483647;
scanf("%d",&n);
while(n--){
int x; scanf("%d",&x);
if (x>max)max=x;
if (x<min)min=x;
}
printf("the maximum value is: %d\nthe minimum value is: %d\n",max,min);
}