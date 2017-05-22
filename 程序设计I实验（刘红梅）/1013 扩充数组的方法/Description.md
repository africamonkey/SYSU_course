# 扩充数组的方法

a# Description：

实现一个函数，扩充数组的大小。

函数声明为：

int * doubleCapacity(int *list, int size, int addSize);

例如，下面的代码的输出为：1 2 3 4 5 0 0 0 0 0

```c
int list[5]={1,2,3,4,5};
int *newlist = doubleCapacity(list,5);
for(int i=0;i<2*5;i++)
  printf("%d "，newlist[i]);
```
 

## 注意：只用实现函数定义即可，main函数已经定义
# Input

第一行为两个数字m和n，m是原来数组的大小，n是增加的大小。m在1和10之间，n在5和10之间。

第二行为输入m个数字，组成维度为m的数组。


# Output

输出扩充后的数组,输出格式为
```c
printf("%d "，newlist[i]);
```

# Hine

学习使用**[malloc](http://www.cplusplus.com/reference/cstdlib/malloc/)**手动申请内存