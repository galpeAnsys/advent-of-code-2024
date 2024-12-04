#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include "../FileHelper.h"
#include "solution.h"


void MatchPattern(std::string& memoryLine, std::regex& pattern, int& sum)
{
	// Iterator to search for matches
	auto matchesBegin = std::sregex_iterator(memoryLine.begin(), memoryLine.end(), pattern);
	auto matchesEnd = std::sregex_iterator();
	for (std::sregex_iterator it = matchesBegin; it != matchesEnd; ++it) {
		std::smatch match = *it;
		auto value = match.str(0);
		int digit1 = std::stoi(match.str(1));
		int digit2 = std::stoi(match.str(2));
		int product = digit1 * digit2;


		std::cout << value + " = " << std::to_string(product) << std::endl;
		sum += product;
	}
}

void day3::Run() {
	//std::vector<std::string> memory = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day3\\sample.txt");
	std::vector<std::string> memory = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day3\\input.txt");
	std::regex pattern(R"(mul\((\d+),(\d+)\))");

	int sum = 0;
	for (auto& memoryLine : memory)
	{
		MatchPattern(memoryLine, pattern, sum);
	}

	std::cout << std::to_string(sum) << std::endl;
}



void day3::Run2() {
	//std::vector<std::string> memory = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day3\\sample.txt");
	std::vector<std::string> memory = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day3\\input.txt");
	std::regex mulPattern(R"(mul\((\d+),(\d+)\))");
	std::regex separatorPattern(R"(don't\(\)|do\(\))");

	for (auto& memoryLine : memory)
	{
		// Iterator to search for matches
		auto matchesBegin = std::sregex_iterator(memoryLine.begin(), memoryLine.end(), separatorPattern);
		std::sregex_token_iterator it(memoryLine.begin(), memoryLine.end(), separatorPattern, -1);
		auto matchesEnd = std::sregex_iterator();
		std::vector<std::string> lines;
		int pos = 0;
		for (std::sregex_iterator it = matchesBegin; it != matchesEnd; ++it) {
			std::smatch match = *it;

			if (pos == 0 && match.position() != pos) {
				lines.push_back(match.prefix());
			}

			if (match.str(0) == "do()") {
				lines.push_back(match.suffix());
			}

			pos = match.position();
		}

		int sum = 0;

		for (auto& line : lines) {
			MatchPattern(line, mulPattern, sum);
		}

		std::cout << std::to_string(sum) << std::endl;

	}
}