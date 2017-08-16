#图书管理系统 说明文档

##运行环境 Environments

Linux (Recommended) or

OS X or

Windows

##编译命令 Compile Command

g++ demo.cpp -o demo

##样例输入

`
1
hahaha
1
ha ha ha
6
3
ha ha ha
1
5
ha ha ha
4
ha ha ha
1
5
ha ha ha
2
ha ha ha
6
7
`

##样例输出

`
Simple Library Management System (Demo)

1: add a book
2: delete a book
3: borrow a book
4: return a book
5: query a book
6: query all books
7: quit

enter your operations: 
======== Process start ========

Input the name of the book: Success!

========= Process end =========
Simple Library Management System (Demo)

1: add a book
2: delete a book
3: borrow a book
4: return a book
5: query a book
6: query all books
7: quit

enter your operations: 
======== Process start ========

Input the name of the book: Success!

========= Process end =========
Simple Library Management System (Demo)

1: add a book
2: delete a book
3: borrow a book
4: return a book
5: query a book
6: query all books
7: quit

enter your operations: 
======== Process start ========

Book Information
Book 0: hahaha        Not Borrowed
Book 1: ha ha ha        Not Borrowed
2 books in the library.

========= Process end =========
Simple Library Management System (Demo)

1: add a book
2: delete a book
3: borrow a book
4: return a book
5: query a book
6: query all books
7: quit

enter your operations: 
======== Process start ========

Input the book name: Confirm borrow: select the ID which you want to borrow

Book 1: ha ha ha        Not Borrowed

enter your choice: Success!

========= Process end =========
Simple Library Management System (Demo)

1: add a book
2: delete a book
3: borrow a book
4: return a book
5: query a book
6: query all books
7: quit

enter your operations: 
======== Process start ========

Input the book name: Book Information
Book 1: ha ha ha        Borrowed

========= Process end =========
Simple Library Management System (Demo)

1: add a book
2: delete a book
3: borrow a book
4: return a book
5: query a book
6: query all books
7: quit

enter your operations: 
======== Process start ========

Input the book name: Confirm return: select the ID which you want to return

Book 1: ha ha ha        Borrowed

enter your choice: Success!

========= Process end =========
Simple Library Management System (Demo)

1: add a book
2: delete a book
3: borrow a book
4: return a book
5: query a book
6: query all books
7: quit

enter your operations: 
======== Process start ========

Input the book name: Book Information
Book 1: ha ha ha        Not Borrowed

========= Process end =========
Simple Library Management System (Demo)

1: add a book
2: delete a book
3: borrow a book
4: return a book
5: query a book
6: query all books
7: quit

enter your operations: 
======== Process start ========

Input the book name: Confirm delete: select the ID which you want to delete

Book 1: ha ha ha        Not Borrowed

enter your choice: Success!

========= Process end =========
Simple Library Management System (Demo)

1: add a book
2: delete a book
3: borrow a book
4: return a book
5: query a book
6: query all books
7: quit

enter your operations: bye
`
