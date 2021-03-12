#pragma once
#include "Book.h"
#include "Book_repo.h"

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction {
	Book addedBook;
	BookRepo& rep;

public:
	UndoAdd(BookRepo& rep, const Book& b) : rep{rep}, addedBook{b} {}

	void doUndo() override {
		rep.eliminate(addedBook);
	}
};

class UndoSterge : public UndoAction {
	Book deletedBook;
	BookRepo& rep;
public:
	UndoSterge(BookRepo& rep, const Book& b) : rep{rep}, deletedBook{b} {}

	void doUndo() override {
		rep.store(deletedBook);
	}
};
