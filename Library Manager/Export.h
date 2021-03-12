#pragma once
#include <string>
#include <vector>
#include "Book.h"

void exportToCVS(const std::string& fName, const std::vector<Book>& books);

void exportToHTML(const std::string& fName, const std::vector<Book>& books);