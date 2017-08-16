#include <bits/stdc++.h>
#include "library.h"

void menu() {
	puts("Simple Library Management System (Demo)");
	puts("");
	puts("1: add a book");
	puts("2: delete a book");
	puts("3: borrow a book");
	puts("4: return a book");
	puts("5: query a book");
	puts("6: query all books");
	puts("7: quit");
	puts("");
	printf("enter your operations: ");
}

int main() {
	lib library;
	while (1) {
		menu();
		int op;
		scanf("%d", &op);
		fgets(buf, BUF_SIZE-1, stdin);
		if (op == 7) {
			puts("bye");
		} else {
			puts("");
			puts("======== Process start ========");
			puts("");
		}
		switch (op) {
			case 1:
				library.add();
				break;
			case 2:
				library.del();
				break;
			case 3:
				library.borrow();
				break;
			case 4:
				library.return_();
				break;
			case 5:
				library.query();
				break;
			case 6:
				library.query_all();
				break;
			case 7:
				exit(0);
				break;
			default:
				puts("Nothing is changed.");
				puts("");
				break;
		}
		puts("========= Process end =========");
	}
}
