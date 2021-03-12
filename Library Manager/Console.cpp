#include "console.h"
#include "Book.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

template <typename T>
T myread(const char* msg) {
	T cmd{};
	while (true) {
		std::cout << std::endl << msg;
		std::cin >> cmd;
		const bool fail = std::cin.fail();
		std::cin.clear();
		const auto& aux = std::cin.ignore(1000, '\n');
		if (!fail && aux.gcount() <= 1) {
			break;
		}
	}
	return cmd;
}

void ConsoleUI::print(const vector<Book>& books) {
	cout << "Books: \n";
	for (const auto& book : books) {
		cout << "----------\n";
		cout << "	Title: " << left << setw(25) << book.getTitle();
		cout << "|	Author: " << left << setw(15) << book.getAuthor();
		cout << "|	Genre: " << left << setw(15) << book.getGenre();
		cout << "|	Date: " << book.getDate();
		cout << '\n';
	}
	cout << "End of list\n";
}


void ConsoleUI::addUI() {
	string title, author, genre;
	int date;

	cout << "Enter title: ";
	cin.ignore();
	std::getline(std::cin, title);

	cout << "Enter author: ";
	std::getline(std::cin, author);

	cout << "Enter genre: ";
	std::getline(std::cin, genre);

	cout << "Enter date: ";
	cin >> date;
	srv.addBook(title, author, genre, date);
	cout << "Book added successfully!\n";
}

void ConsoleUI::addToBasketUI() {
	string title, author;
	cout << "Enter title: ";
	cin.ignore();
	std::getline(std::cin, title);

	cout << "Enter author: ";
	std::getline(std::cin, author);

	print(srv.addToCos(title, author));
}

void ConsoleUI::elimitateBookUI() {
	string title, author;
	cout << "Enter title: ";
	cin.ignore();
	std::getline(std::cin, title);

	cout << "Enter author: ";
	std::getline(std::cin, author);

	srv.eliminateBook(title, author);
	print(srv.getAllBooks());
}


void ConsoleUI::start() {
	string title;
	while (true) {
		cout << "Menu:\n";
		cout <<
			"1 - Add\n2 - Print all\n3 - Sort by title\n4 - Sort by author\n5 - Sort by date|genre\n6 - Filter title\n7 - Filter date\n8- Undo\n9 - Add to basket\n10 - Empty basket\n11 - Add random\n12 - Export to CVS\n13 - Export to HTML\n14 - Eliminate book\n0 - Exit\nCommand: ";
		int cmd;
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				addUI();
				break;
			case 2:
				print(srv.getAllBooks());
				break;
			case 3:
				cout << "Books sorted by title: \n";
				print(srv.sortByTitle());
				break;
			case 4:
				cout << "Books sorted by author: \n";
				print(srv.sortByAuthor());
				break;
			case 5:
				cout << "Books sorted by date: \n";
				print(srv.sortByGenreDate());
				break;
			case 6:
				cout << "Enter the title you want to filter: ";
				cin.ignore();
				std::getline(std::cin, title);
				print(srv.getFilterByTitle(title));
				break;
			case 7:
				cout << "Enter the date you want to filter: ";
				int d;
				cin >> d;
				print(srv.getFilterByDate(d));
				break;
			case 8:
				srv.undo();
				print(srv.getAllBooks());
				break;
			case 9:
				addToBasketUI();
				break;
			case 10:
				print(srv.golesteCos());
				break;
			case 11:
				print(srv.addRandom(myread<int>("Quantity: ")));
				break;
			case 12:
				srv.exportaCosCVS(myread<string>("CVS File: "));
				break;
			case 13:
				srv.exportaCosHTML(myread<string>("HTML File: "));
				break;
			case 14:
				elimitateBookUI();
				break;
			case 0:
				return;
			default:
				cout << "Invalid command\n";
			}
		}
		catch (const BookException& ex) {
			cout << ex.getMsg() << std::endl;
		}
		catch (const ValidateException& ex) {
			cout << ex << "\n";
		}
	}
}
