#pragma once
#include "Book.h"
#include "Book_repo.h"
#include <string>
#include "List.h"
#include <vector>
#include <functional>
#include "validator.h"
#include "undo.h"
#include "CosBook.h"
#include "export.h"

class BookLibrary {
	BookRepo& repo;

	BookValidator& validator;

	std::vector<unique_ptr<UndoAction>> undoActions;

	//vector<Book> generalSort(bool (*maiMicF)(const Book&, const Book&));
	//vector<Book> filter(function<bool(const Book&)> fct);

	CosBook cos;

public:
	BookLibrary(BookRepo& repo, BookValidator& val) : repo{repo}, validator{val} {}
	~BookLibrary();
	//Nu permitem copierea de obiecte de tip BookLibrary
	BookLibrary(const BookLibrary& ot) = delete;
	void operator=(const BookLibrary& ot) = delete;

	const std::vector<Book>& getAllBooks() const;

	//const vector<Book>& getAll() {
	//	return repo.getAll();
	//}

	void addBook(const string& title, const string& author, const string& genre, const int& date);

	void eliminateBook(const string& title, const string& author);

	std::vector<Book> sortByTitle() const;

	std::vector<Book> sortByAuthor() const;

	std::vector<Book> sortByGenreDate() const;

	std::vector<Book> getFilterByDate(int date) const;

	std::vector<Book> getFilterByTitle(string title) const;

	void undo();

	const std::vector<Book>& addToCos(const string& title, const string& author);

	const std::vector<Book>& addRandom(int cate);

	const std::vector<Book>& golesteCos();

	const std::vector<Book>& toateDinCos();

	void exportaCosCVS(string fName) const;

	void exportaCosHTML(string fName) const;

};

void testService();
