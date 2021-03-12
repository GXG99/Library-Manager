#pragma once
#include <string>
#include <iostream>


using namespace std;


class BookException {
	string msg;
public:
	BookException(const string& m) : msg{m} {};

	string getMsg() const {
		return msg;
	}
};


class Book {
	string title;
	string author;
	string genre;
	int date;
public:

	//Constructor with parameters
	Book(const string _title, const string _author, const string _genre, const int _date) : title{_title},
	                                                                                        author{_author},
	                                                                                        genre{_genre},
	                                                                                        date{_date} { }

	Book(const Book& book) = default;


	//Book(const Book& ot): title{ot.title}, author{ot.author}, genre{ot.genre}, date{ot.date} {
	//	cout << "Constructor: " << ot.author << " " << ot.title << " " << ot.genre << " " << ot.date << "\n";
	//}

	Book& operator=(const Book& book) = default;

	string getTitle() const {
		return title;
	}

	string getAuthor() const {
		return author;
	}

	string getGenre() const {
		return genre;
	}

	int getDate() const {
		return date;
	}

	void setDate(int d) {
		this->date = d;
	}
};

int cmpTitle(const Book& book1, const Book& book2);

int cmpAuthor(const Book& book1, const Book& book2);

void testBook();
