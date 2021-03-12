#pragma once
#include <string>
#include "Book.h"
#include "List.h"
#include <vector>

using namespace std;

class ValidateException {
	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) : msgs{errors} {}

	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class BookValidator {
public:
	void validate(const Book& book);
};

void testValidator();
