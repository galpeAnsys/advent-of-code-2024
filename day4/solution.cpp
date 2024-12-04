#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include "../FileHelper.h"
#include "solution.h"

std::regex ptrnXmasLtr(R"(XMAS)");


int FindAllHorizontalLeftToRight(std::vector<std::string> lines) {
	int c = 0;

	for (std::string line : lines) {
		auto matchesBegin = std::sregex_iterator(line.begin(), line.end(), ptrnXmasLtr);
		auto matchesEnd = std::sregex_iterator();

		c += std::distance(matchesBegin, matchesEnd);
	}

	return c;
}

void MyRun(std::string path) {
	std::vector<std::string> lines = ReadInput(path);
	int res = 0;
	int leftToRight = FindAllHorizontalLeftToRight(lines);

	std::cout << "Left to Right XMAS: " + std::to_string(leftToRight) << std::endl;

	res += leftToRight;

	std::cout << "Total count: " + std::to_string(res) << std::endl;
}

void day4::Run() {
	std::cout << "------ SAMPLE 1 -------" << std::endl;

	MyRun("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day4\\sample1.txt");

	std::cout << "------ SAMPLE 2 -------" << std::endl;

	MyRun("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day4\\sample2.txt");

	std::cout << "------ SAMPLE 3 -------" << std::endl;

	MyRun("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day4\\sample3.txt");

}

void day4::Run2() {
}