#include "Book_repo.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

void BookRepoFile::loadFromFile() {
	ifstream in(fName);

	if (!in.is_open()) {
		throw BookException{"Unable to open file: " + fName};
	}
	while (!in.eof()) {
		string title;
		in >> title;

		string author;
		in >> author;

		string genre;
		in >> genre;

		int date;
		in >> date;

		if (in.eof()) {
			break;
		}
		Book b{title.c_str(), author.c_str(), genre.c_str(), date};
		BookRepo::store(b);
	}
	in.close();
}

void BookRepoFile::writeToFile() {
	ofstream out(fName);
	if (!out.is_open()) {
		throw BookException("Unable to open file:");
	}

	for (auto& b : getAll()) {
		out << b.getTitle();
		out << endl;
		out << b.getAuthor();
		out << endl;
		out << b.getGenre();
		out << endl;
		out << b.getDate();
		out << endl;
	}
	out.close();
}

void testFileRepo() {
	std::ofstream out("testBooks.txt", std::ios::trunc);
	out.close();
	BookRepoFile repF{"testBooks.txt"};
	repF.store(Book{"aaa", "bbb", "ccc", 1000});

	BookRepoFile repF2{"testBooks.txt"};
	auto b = repF2.find("aaa", "bbb");
	assert(b.getDate() == 1000);
	try {
		repF2.find("aaa2", "bbb2");
		assert(false);
	}
	catch (BookException&) { }

	repF2.eliminate(Book{"aaa", "bbb", "ccc", 1000});
	assert(repF2.getAll().size() == 0);
	try {
		repF2.eliminate(Book{"aaa", "bbb", "ccc", 1000});
		assert(false);
	}
	catch (BookException&) { }

	BookRepoFile repF3{"testBooks.txt"};
	assert(repF3.getAll().size() == 0);

	try {
		BookRepoFile repF4{"te/stPets.txt"};
		assert(false);
	}
	catch (BookException&) {
		assert(true);
	}
}

void testBookRepo() {
	testFileRepo();
}
