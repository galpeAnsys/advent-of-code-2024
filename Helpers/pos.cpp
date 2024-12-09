
#include <iostream>
#include <string>
#include "../FileHelper.h"
#include "pos.h"


pos::pos() : r(0), c(0) {}
pos::pos(int row, int col) : r(row), c(col) {}

void pos::display() const {
	std::cout << "(" << r << ", " << c << ")" << std::endl;
}

std::string pos::toString() const {
	return "(" + Str(r) + "," + Str(c) + ")";
}