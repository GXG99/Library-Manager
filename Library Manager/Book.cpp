#include "Book.h"
#include <cassert>


void testBook() {
	Book bb1{"a", "a", "a", 2};
	Book bb2{"b", "b", "b", 3};
	assert(cmpTitle(bb1, bb2) < 0);
	assert(cmpTitle(bb2, bb1) > 0);
	assert(cmpTitle(bb1, bb1) == 0);

	assert(cmpAuthor(bb1, bb2) < 0);
	assert(cmpAuthor(bb2, bb1) > 0);
	assert(cmpAuthor(bb1, bb1) == 0);
}

int cmpTitle(const Book& book1, const Book& book2) {
	if (book1.getTitle() == book2.getTitle()) {
		return 0;
	}
	if (book1.getTitle() < book2.getTitle()) {
		return -1;
	}
	return 1;
}

int cmpAuthor(const Book& book1, const Book& book2) {
	if (book1.getAuthor() == book2.getAuthor()) {
		return 0;
	}
	if (book1.getAuthor() < book2.getAuthor()) {
		return -1;
	}
	return 1;
}
