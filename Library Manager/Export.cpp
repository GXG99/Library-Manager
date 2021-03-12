#include "Export.h"
#include "Book.h"
#include <fstream>
#include <string>
#include <vector>

void exportToCVS(const std::string& fName, const std::vector<Book>& books) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {
		throw BookException("Unable to open file" + fName);
	}
	for (const auto& b : books) {
		out << b.getTitle() << ",";
		out << b.getAuthor() << ",";
		out << b.getGenre() << ",";
		out << b.getDate() << std::endl;
	}
	out.close();
}

void exportToHTML(const std::string& fName, const std::vector<Book>& books) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {
		throw BookException("Unable to open file" + fName);
	}
	out << "<html><body>" << std::endl;
	out << "<table_border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& b : books) {
		out << "<tr>" << std::endl;
		out << "<td>" << b.getTitle() << "</td>" << std::endl;
		out << "<td>" << b.getAuthor() << "</td>" << std::endl;
		out << "<td>" << b.getGenre() << "</td>" << std::endl;
		out << "<td>" << b.getDate() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}
