#pragma once
#include "Book_service.h"
#include "Book.h"
#include <vector>


class ConsoleUI {
	BookLibrary& srv;

	void addUI();

	void addToBasketUI();

	void elimitateBookUI();

	void print(const vector<Book>& book);
public:
	ConsoleUI(BookLibrary& srv): srv{srv} {}

	ConsoleUI(const ConsoleUI& ot) = delete;

	void start();
};
