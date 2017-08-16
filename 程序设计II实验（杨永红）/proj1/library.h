#include <bits/stdc++.h>

#define BUF_SIZE 100020
#define ALL 1

char buf[BUF_SIZE];

class book {
	public:
	book() {}
	//argument _borrowed represents whether the book is borrowed
	book(int _borrowed) {
		printf("Input the name of the book: ");
		fflush(stdin);
		do {
			fgets(buf, BUF_SIZE-1, stdin);
		} while (strlen(buf) < 2);
		int l = strlen(buf) - 1;
		while (l >= 0 && buf[l] == '\n') buf[l--] = 0;
		name = buf;
		borrowed = _borrowed;
	}
	//mark the book as borrowed
	void borrow() { borrowed = 1; }
	//mark the book as returned
	void return_() { borrowed = 0; }
	//get the name of the book
	std::string getname() { return name; }
	//get the borrowed mark of the book
	bool getborrowed() { return borrowed; }
	
	private:
	std::string name;
	bool borrowed;
};

class lib {
	public:
	//print the information of the book.
	//user can select which book to borrow/return/delete
	//argument operation_type represents the type of operation(borrow/return/delete)
	//argument all represents query all or not
	int print(std::string operation_type, int all = 0) {
		std::string book_name;
		
		if (all != ALL) {
			//spaces are accepted.
			std::cout << "Input the book name: ";
			fflush(stdin);
			do {
				fgets(buf, BUF_SIZE-1, stdin);
			} while (strlen(buf) < 2);
			int l = strlen(buf) - 1;
			while (l >= 0 && buf[l] == '\n') buf[l--] = 0;
			book_name = buf;
		}
		
		if (operation_type == "") {
			std::cout << "Book Information" << std::endl;
		} else {
			std::cout << "Confirm " << operation_type << 
				": select the ID which you want to " << operation_type << std::endl;
			std::cout << std::endl;
		}
		int ok = 0;
		for (int i = 0; i < books.size(); ++i)
			if (books[i].getname() == book_name || all == ALL) {
				std::cout << "Book " << i << ": " <<
					books[i].getname() << "        " <<
					(books[i].getborrowed() ? "Borrowed" : "Not Borrowed")
					<< std::endl;
				ok = 1;
			}
		if (all == ALL) {
			std::cout << books.size() << " books in the library." << "\n";
			return 1;
		}
		if (ok == 0) {
			std::cout << "error: there is no book called \"" << book_name << "\"\n\n";
			return 0;
		}
		if (operation_type == "") return 1;
		std::cout << std::endl << "enter your choice: ";
		fflush(stdin);
		return 1;
	}
	//add a book and return success.
	void add() {
		books.push_back(book(0));
		puts("Success!");
		puts("");
	}
	
	//delete a book and return success.
	void del() {
		if (!print("delete")) return;
		int y;
		scanf("%d", &y);
		books.erase(books.begin() + y);
		puts("Success!");
		puts("");
	}
	
	//borrow a book and return success.
	void borrow() {
		if (!print("borrow")) return;
		int y;
		scanf("%d", &y);
		books[y].borrow();
		puts("Success!");
		puts("");
	}
	
	//return a book and return success.
	void return_() {
		if (!print("return")) return;
		int y;
		scanf("%d", &y);
		books[y].return_();
		puts("Success!");
		puts("");
	}
	
	//query a book.
	void query() {
		print("");
		puts("");
	}
	
	//query all books.
	void query_all() {
		print("", ALL);
		puts("");
	}
	private:
	std::vector<book> books;
};
