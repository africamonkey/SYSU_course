#include<stdio.h>
 
int main() {
        int num;
        scanf("%d", &num);
 
        while (num--) {
                int a[100], i = 0, j = 0;
                int length;
                scanf("%d", &length);
                while (scanf("%d", &a[i])) {
                        i++;
                        if (i == length)
                                break;
                }
 
                for (i = 0; i < length; i++)
                        for (j = i+1; j < length; j++)
                                if (a[i] > a[j]) {
                                        int temp = a[i];
                                        a[i] = a[j];
                                        a[j] = temp;
                                }
                if (length == 1) {
                        printf("%d \n", a[0]);
                        continue;
                }
                printf("%d ", a[0]);
                for (i = 1; i < length; i++)
                        if (a[i] != a[i-1])
                                printf("%d ", a[i]);
                printf("\n");
        }
        return 0;
}