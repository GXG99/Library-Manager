#include "Validator.h"
#include <assert.h>
#include <sstream>

void BookValidator::validate(const Book& book) {
	vector<string> msgs;
	if (book.getDate() < 0) msgs.push_back("Negative date!\n");
	if (book.getGenre().empty()) msgs.push_back("Void genre!\n");
	if (book.getTitle().empty()) msgs.push_back("Void title!\n");
	if (book.getAuthor().empty()) msgs.push_back("Void author!\n");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	BookValidator validator;
	Book book{"", "", "", -1};
	try {
		validator.validate(book);
	}
	catch (const ValidateException& ex) {
		stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("Negative") >= 0);
		assert(mesaj.find("Void") >= 0);
	}
}
