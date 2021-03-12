#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Book.h"


using namespace std;


class CosBook {
	vector<Book> inCos;
public:
	CosBook() = default;

	void addInCos(const Book& book) {
		inCos.push_back(book);
	}

	void unFill() {
		inCos.clear();
	}

	void fill(size_t quantity, vector<Book> all) {
		std::shuffle(all.begin(), all.end(), default_random_engine(random_device{}()));
		while (inCos.size() < quantity && all.size() > 0) {
			inCos.push_back(all.back());
			all.pop_back();
		}
	}

	const vector<Book>& lista() const {
		return inCos;
	}
};
