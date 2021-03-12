#include "Book_service.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <fstream>

void BookLibrary::addBook(const string& title, const string& author, const string& genre, const int& date) {
	Book book{title, author, genre, date};
	validator.validate(book);
	repo.store(book);
	undoActions.push_back(std::make_unique<UndoAdd>(repo, book));
}

void BookLibrary::eliminateBook(const string& title, const string& author) {
	Book deletedBook = repo.find(title, author);
	repo.eliminate(deletedBook);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, deletedBook));
}


void BookLibrary::undo() {
	if (undoActions.empty()) {
		throw BookException{"Cannot undo anymore"};
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();

}

BookLibrary::~BookLibrary() {}

const std::vector<Book>& BookLibrary::getAllBooks() const {
	return repo.getAll();
}

std::vector<Book> BookLibrary::sortByTitle() const {
	auto temp = repo.getAll();
	std::sort(temp.begin(), temp.end(), [](const Book& b1, const Book& b2) {
		return b1.getTitle() < b2.getTitle();
	});
	return temp;
}

std::vector<Book> BookLibrary::sortByAuthor() const {
	auto temp = repo.getAll();
	std::sort(temp.begin(), temp.end(), [](const Book& b1, const Book& b2) {
		return b1.getAuthor() < b2.getAuthor();
	});
	return temp;
}

std::vector<Book> BookLibrary::sortByGenreDate() const {
	auto temp = repo.getAll();
	std::sort(temp.begin(), temp.end(), [](const Book& b1, const Book& b2) {
		if (b1.getGenre() == b2.getGenre()) {
			return b1.getDate() < b2.getDate();
		}
		return b1.getGenre() < b2.getGenre();
	});
	return temp;
}

std::vector<Book> BookLibrary::getFilterByDate(int date) const {
	std::vector<Book> temp;
	auto& all = repo.getAll();
	std::copy_if(all.begin(), all.end(), back_inserter(temp), [=](const Book& b) {
		return b.getDate() == date;
	});
	return temp;
}

std::vector<Book> BookLibrary::getFilterByTitle(string title) const {
	std::vector<Book> temp;
	auto& all = repo.getAll();
	std::copy_if(all.begin(), all.end(), back_inserter(temp), [=](const Book& b) {
		return b.getTitle() == title;
	});
	return temp;
}


const std::vector<Book>& BookLibrary::addToCos(const string& title, const string& author) {
	const Book& b = repo.find(title, author);
	cos.addInCos(b);
	return cos.lista();
}

const std::vector<Book>& BookLibrary::addRandom(int cate) {
	cos.fill(cate, repo.getAll());
	return cos.lista();
}

const std::vector<Book>& BookLibrary::golesteCos() {
	cos.unFill();
	return cos.lista();
}

const std::vector<Book>& BookLibrary::toateDinCos() {
	return cos.lista();
}

void BookLibrary::exportaCosCVS(string fName) const {
	exportToCVS(fName, cos.lista());
}

void BookLibrary::exportaCosHTML(string fName) const {
	exportToHTML(fName, cos.lista());
}

void testAdd() {
	BookRepo repo;
	BookValidator validator;
	BookLibrary srv{repo, validator};
	srv.addBook("aaa", "bbb", "ccc", 3);
	assert(srv.getAllBooks().size() == 1);
	srv.addBook("ddd", "eee", "fff", 2);
	assert(srv.getAllBooks().size() == 2);
	try {
		srv.addBook("aaa", "bbb", "ccc", 3);
		assert(false);
	}
	catch (BookException&) {
		assert(true);
	}
}

void testFilter() {
	BookRepo repo;
	BookValidator validator;
	BookLibrary srv{repo, validator};
	srv.addBook("aaa", "bbb", "ccc", 3);
	srv.addBook("ddd", "eee", "fff", 4);
	srv.addBook("ggg", "hhh", "iii", 5);

	std::vector<Book> filtered = srv.getFilterByDate(3);
	assert(filtered.size() == 1);
	assert(filtered[0].getDate() == 3);

	filtered = srv.getFilterByTitle("ddd");
	assert(filtered.size() == 1);
	assert(filtered[0].getDate() == 4);
}

void testSort() {
	BookRepo repo;
	BookValidator validator;
	BookLibrary srv{repo, validator};
	srv.addBook("ddd", "eee", "ccc", 4);
	srv.addBook("aaa", "bbb", "ccc", 3);
	srv.addBook("ggg", "hhh", "iii", 5);

	std::vector<Book> sorted = srv.sortByTitle();
	assert(sorted[0].getDate() == 3);
	assert(sorted[1].getDate() == 4);

	std::vector<Book> sorted2 = srv.sortByAuthor();
	assert(sorted[0].getDate() == 3);
	assert(sorted[1].getDate() == 4);

	std::vector<Book> sorted3 = srv.sortByGenreDate();
	assert(sorted[0].getDate() == 3);
	assert(sorted[1].getDate() == 4);
}

void testUndo() {
	BookRepo repo;
	BookValidator validator;
	BookLibrary srv{repo, validator};
	srv.addBook("ddd", "eee", "fff", 4);
	srv.addBook("aaa", "bbb", "ccc", 3);
	srv.addBook("ggg", "hhh", "iii", 5);
	srv.undo();
	assert(srv.getAllBooks().size() == 2);
	srv.undo();
	srv.undo();
	assert(srv.getAllBooks().size() == 0);
	try {
		srv.undo();
		assert(false);
	}
	catch (BookException& ex) {
		assert(ex.getMsg() == "Cannot undo anymore");
	}
	srv.addBook("ddd", "eee", "fff", 4);
	srv.addBook("aaa", "bbb", "ccc", 3);
	srv.addBook("ggg", "hhh", "iii", 5);
	assert(srv.getAllBooks().size() == 3);
	srv.eliminateBook("ddd", "eee");
	assert(srv.getAllBooks().size() == 2);
	srv.undo();
	assert(srv.getAllBooks().size() == 3);
}

void testCos() {
	BookRepo repo;
	BookValidator validator;
	BookLibrary srv{repo, validator};
	srv.addBook("ddd", "eee", "fff", 4);
	srv.addBook("aaa", "bbb", "ccc", 3);
	srv.addBook("ggg", "hhh", "iii", 5);
	assert(srv.toateDinCos().size() == 0);
	srv.addToCos("ddd", "eee");
	assert(srv.toateDinCos().size() == 1);
	try {
		srv.addToCos("1ddd", "1eee");
		assert(false);
	}
	catch (BookException&) {
		assert(true);
	}
	srv.golesteCos();
	assert(srv.toateDinCos().size() == 0);
}


void testExport() {
	BookRepo repo;
	BookValidator validator;
	BookLibrary srv{repo, validator};
	srv.addBook("ddd", "eee", "fff", 4);
	srv.addBook("aaa", "bbb", "ccc", 3);
	srv.addBook("ggg", "hhh", "iii", 5);
	srv.addRandom(3);
	srv.exportaCosCVS("testExport.cvs");
	std::ifstream in("testExport.cvs");
	assert(in.is_open());
	int countLines = 0;
	while (!in.eof()) {
		string line;
		in >> line;
		countLines++;
	}
	in.close();
	assert(countLines == 4);
	srv.exportaCosHTML("testExport.html");
	in.open("testExport.html");
	assert(in.is_open());

	try {
		srv.exportaCosCVS("test/Export.cvs");
		assert(false);
	}
	catch (BookException&) {
		assert(true);
	}
	try {
		srv.exportaCosHTML("a/b/c/Export.html");
		assert(false);
	}
	catch (BookException&) {
		assert(true);
	}

}

void testDelete() {
	BookRepo repo;
	BookValidator validator;
	BookLibrary srv{repo, validator};
	srv.addBook("ddd", "eee", "fff", 4);
	srv.addBook("aaa", "bbb", "ccc", 3);
	srv.addBook("ggg", "hhh", "iii", 5);
	srv.eliminateBook("ddd", "eee");
	assert(srv.getAllBooks().size() == 2);
}

void testService() {
	testAdd();
	testFilter();
	testSort();
	testUndo();
	testCos();
	testExport();
	testDelete();
}
