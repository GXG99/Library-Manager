#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Book_repo.h"
#include "Validator.h"
#include "Book_service.h"
#include "Console.h"


using namespace std;

void add(BookLibrary& srv) {
	srv.addBook("Foucault's Pendulum", "Umberto Eco", "Fiction", 1988);
	srv.addBook("The Neverending Story", "Michael Ende", "Fiction", 1979);
	srv.addBook("Anna Karenina", "Lev Tolstoi", "Realist novel", 1877);
	srv.addBook("The Idiot Brain", "Dean Burnett", "Humor", 2016);
}

void run_tests() {
	testBook();
	testBookRepo();
	testValidator();
	testService();
}

int main() {

	cout << "Library Manager v0.1 \n";
	run_tests();

	{
		BookRepo repo;
		BookValidator validator;
		BookLibrary srv{repo, validator};
		add(srv); //Add default values
		ConsoleUI ui{srv};
		ui.start();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
