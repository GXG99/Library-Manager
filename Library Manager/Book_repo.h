#pragma once
#include "Book.h"
#include <vector>
#include "List.h"
#include <string>
#include <ostream>

using namespace std;

class BookRepo {
	vector<Book> all_books;

	bool exist(const Book& book);

public:
	BookRepo() = default;

	/*
	 * Object copying is denied
	 */
	BookRepo(const BookRepo& ot) = delete;
	virtual ~BookRepo() = default;

	/*
	 * Function that stores a pet.
	 * Throw exception if a book already exists
	 */
	virtual void store(const Book& b) {
		auto found = find_if(all_books.begin(), all_books.end(), [b](const Book& bb) {
			return bb.getTitle() == b.getTitle() && bb.getAuthor() == b.getAuthor();
		});
		if (found != all_books.end()) {
			throw BookException{"Existent book!"};
		}
		all_books.push_back(b);
	}

	const Book& find(string title, string author) {
		auto found = find_if(all_books.begin(), all_books.end(), [&](const Book& bb) {
			return bb.getTitle() == title && bb.getAuthor() == author;
		});
		if (found == all_books.end()) {
			throw BookException{"Inexistent book"};
		}
		return *found;
	}

	/*
	 * Function that finds an existing book in the repository.
	 * Throws exception if a book is not found.
	 */
	virtual void eliminate(const Book& b) {
		auto found = find_if(all_books.begin(), all_books.end(), [b](const Book& bb) {
			return bb.getAuthor() == b.getAuthor() && bb.getTitle() == b.getTitle();
		});
		if (found == all_books.end()) {
			throw BookException{"Inexistent book"};
		}
		auto rez = all_books.erase(found);
	}

	/*
	 * Return all the stored books
	 */
	const vector<Book>& getAll() const {
		return all_books;
	}
};

class BookRepoFile : public BookRepo {
private:
	string fName;
	void loadFromFile();
	void writeToFile();
public:
	BookRepoFile(string fName) : BookRepo(), fName{fName} {
		loadFromFile();
	}

	void store(const Book& b) override {
		BookRepo::store(b);
		writeToFile();
	}

	void eliminate(const Book& b) override {
		BookRepo::eliminate(b);
		writeToFile();
	}
};

void testBookRepo();
