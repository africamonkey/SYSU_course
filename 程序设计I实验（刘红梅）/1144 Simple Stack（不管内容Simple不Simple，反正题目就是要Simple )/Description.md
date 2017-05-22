# Simple Stack（不管内容Simple不Simple，反正题目就是要Simple )

# description

This problem asks you create a stack using a array. What is stack?

> In computer science, a stack is an abstract data type that serves as a collection of elements,
> with two principal operations: push, which adds an element to the collection, and pop, which removes the most 
> recently added element that was not yet removed.
> &ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;--[Wikipedia](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

In the header file ``stack.h``, there are several functions:  
\(a\) ``stack_constructor``  
&ensp;This function will create a new stack by get a block memory from operate system.  
\(b\) ``stack_destructor``  
&ensp;"free" the block of memory in stack you created.  
\(c\) ``stack_top``  
&ensp;Get the top of a stack. If the stack is empty, this function returns 0. If the stack is not empty, assign the value of the top to where the second agrument points.  
\(d\) ``stack_push``
&ensp;If the size of the stack is smaller than ``STACK_MAX_SIZE``, push a number into stack and return 1. Otherwise, return 0.  
\(e\) ``stack_pop``
&ensp;If the stack is not empty, return 1 and pop the top from stack. Otherwise, reutrn 0.

# Input
The input is not important.
# Output
The output is not important too.

----

**more information is in ``main``**

----

# Hint

> <span style="color:red;font-weight:bolder">如果你很确信掌握了这部分的知识点，你可以直接做题  
> 否则, 还是看一下吧</span>

1. What is stack?

Stack is a LIFO(Last-in First-out) struct. 

A stack with data is similar with a stack in real, for example, a stack of book. There are serval properties:  
a. you can only move one book at the top of this book stack at once.  
b. If you want to get a book not at the top, you must remove all the books above it.  
c. Similarly, if you want to add a book, you can only put it on the top of this stack.  

```
Remove D:
              D
+     +    +  ^  +
|  D  |    |     |
|  C  |    |  C  |
|  B  |    |  B  |
|  A  |    |  A  |
+-----+    +-----+

```

```
Remove B:
              D          C          B
+     +    +  ^  +    +  ^  +    +  ^  +
|  D  |    |     |    |     |    |     |
|  C  |    |  C  |    |     |    |     |
|  B  |    |  B  |    |  B  |    |     |
|  A  |    |  A  |    |  A  |    |  A  |
+-----+    +-----+    +-----+    +-----+

```

```
Add E:
              
+     +    +  ˇ  +
|     |    |  E  |
|  D  |    |  D  |
|  C  |    |  C  |
|  B  |    |  B  |
|  A  |    |  A  |
+-----+    +-----+
```

```
Add E on C:
              D
+     +    +  ^  +    +  ˇ  +
|  D  |    |     |    |  E  |
|  C  |    |  C  |    |  C  |
|  B  |    |  B  |    |  B  |
|  A  |    |  A  |    |  A  |
+-----+    +-----+    +-----+
```
<p><a href="https://en.wikipedia.org/wiki/Stack_(abstract_data_type)"><img src="https://upload.wikimedia.org/wikipedia/commons/b/b4/Lifo_stack.png" alt="Lifo stack.png"></a></p>

2. How to represent a stack?

> 你们什么时候才会学到结构体啊！ -- From some TA.  
> 等你们学完了指针和结构体，就可以搞事情了！  -- From Author.

A good idea is using a struct to store a stack and its status.  
Unfortunately, this point may not be learned now. So, the author has an ugly trade, using an array to represent a stack.  

To represent a stack, there are two significant variable. One is the current size of the stack, which helps you find the top of the stack. The other is a block of memory, which stores all the data of a stack.  
Now, we stores the size at the first of the array, and use the rest of the array to store the data.  
For example, an array ``int arr[12] = {4, 3, 2, 1, 8, 7, 7, 7, 2, 4, 5, 6}``, represents the stack below:

```
+     +
|  8  |
|  1  |
|  2  |
|  3  |
+-----+
```

And ``arr[0]`` is the size 4, ``arr[1]`` is the bottom of this stack, ``arr[4]`` is the top.  
When we add a number, for example, 4 to this stack, the number will append to this array. The array will become to ``5 3 2 1 8 4 7 7 2 4 5 6``.

```
+     +
|  4  |
|  8  |
|  1  |
|  2  |
|  3  |
+-----+
```
If you want to remove a number from the top of the stack, the size will minus one <del>second</del>.
The array become to ``4 3 2 1 8 4 7 7 2 4 5 6``.  

+ A Small Hint: we do not care what is it if it beyond the size of stack. For ``arr[0]`` = 1, ``arr[2]`` can be any value.  
+ Another small hint: ``arr[arr[0]]`` is the top of the stack.  


## enjoy reading

If you want to get more details, just google it. \_\(:з」∠\)\_