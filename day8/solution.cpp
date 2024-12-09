#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include <unordered_set>
#include <unordered_map>
#include "../FileHelper.h"
#include "../Helpers/pos.h"
#include "solution.h"

std::string vectorToString(std::vector<pos> list) {
	std::string res;
	for (auto& p : list)
	{
		res += p.toString() + ", ";
	}

	return res;
}

std::string setToString(std::unordered_set<pos> set) {
	std::string res;
	for (auto& p : set)
	{
		res += p.toString() + ", ";
	}

	return res;
}

bool inBounds(int rMax, int cMax, pos val) {
	if (val.r < 0 || val.r >= rMax ||
		val.c < 0 || val.c >= cMax) {
		return false;
	}
	return true;
}

std::unordered_map<char, std::vector<pos>> parseAntennas(std::vector<std::string> grid) {
	std::unordered_map<char, std::vector<pos>> antennas;

	for (size_t r = 0; r < grid.size(); r++)
	{
		auto& line = grid[r];
		for (size_t c = 0; c < line.size(); c++)
		{
			auto& val = line[c];
			if (val != '.') {

				antennas[val].push_back(pos(r, c));
			}
		}
	}

	return antennas;
}

std::unordered_set<pos> solveForAntinodes(std::unordered_map<char, std::vector<pos>> antennas, std::vector<std::string> grid) {
	std::unordered_set<pos> allAntinodes;

	for (auto& an : antennas)
	{
		std::unordered_set<pos> antinodes;
		for (size_t i = 0; i < an.second.size(); i++)
		{
			for (size_t j = i + 1; j < an.second.size(); j++)
			{
				auto& p1 = an.second[i];
				auto& p2 = an.second[j];

				auto rDiff = p2.r - p1.r;
				auto cDiff = p2.c - p1.c;

				auto antinode1 = pos(p1.r - rDiff, p1.c - cDiff);
				auto antinode2 = pos(p2.r + rDiff, p2.c + cDiff);

				if (inBounds(grid.size(), grid[0].size(), antinode1)) {
					antinodes.insert(antinode1);
					allAntinodes.insert(antinode1);
				}

				if (inBounds(grid.size(), grid[0].size(), antinode2)) {
					antinodes.insert(antinode2);
					allAntinodes.insert(antinode2);

				}

			}
		}

		std::cout << "[" + std::to_string(an.first) + "] " + vectorToString(an.second) + " >> " + setToString(antinodes) << std::endl;
	}

	return allAntinodes;
}

void displayAntinodes(std::vector<std::string> grid, std::unordered_set<pos> allAntinodes) {
	std::vector<std::string> gCopy(grid);

	for (auto& a : allAntinodes) {
		gCopy[a.r][a.c] = '#';
	}

	for (size_t r = 0; r < gCopy.size(); r++)
	{
		auto& line = gCopy[r];
		for (size_t c = 0; c < line.size(); c++)
		{
			auto& val = line[c];
			std::cout << val;
		}

		std::cout << std::endl;
	}
}

void day8::Run() 
{
	//std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day8\\sample1.txt");
	std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day8\\input.txt");

	std::unordered_map<char, std::vector<pos>>antennas(parseAntennas(grid));
	std::unordered_set<pos> allAntinodes(solveForAntinodes(antennas, grid));

	displayAntinodes(grid, allAntinodes);

	std::cout << Str(allAntinodes.size()) << std::endl;
}

std::unordered_set<pos> solveForAntinodes2(std::unordered_map<char, std::vector<pos>> antennas, std::vector<std::string> grid) {
	std::unordered_set<pos> allAntinodes;

	for (auto& an : antennas)
	{
		std::unordered_set<pos> antinodes;
		for (size_t i = 0; i < an.second.size(); i++)
		{
			for (size_t j = i + 1; j < an.second.size(); j++)
			{
				auto& p1 = an.second[i];
				auto& p2 = an.second[j];

				auto rDiff = p2.r - p1.r;
				auto cDiff = p2.c - p1.c;

				auto antinode1 = p1;
				while (inBounds(grid.size(), grid[0].size(), antinode1)) {
					antinodes.insert(antinode1);
					allAntinodes.insert(antinode1);

					antinode1 = pos(antinode1.r - rDiff, antinode1.c - cDiff);
				}

				auto antinode2 = p2;
				while (inBounds(grid.size(), grid[0].size(), antinode2)) {
					antinodes.insert(antinode2);
					allAntinodes.insert(antinode2);

					antinode2 = pos(antinode2.r + rDiff, antinode2.c + cDiff);
				}

			}
		}

		std::cout << "[" + std::to_string(an.first) + "] " + vectorToString(an.second) + " >> " + setToString(antinodes) << std::endl;
	}

	return allAntinodes;
}

void day8::Run2() {
	//std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day8\\sample1.txt");
	std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day8\\input.txt");

	std::unordered_map<char, std::vector<pos>>antennas(parseAntennas(grid));
	std::unordered_set<pos> allAntinodes(solveForAntinodes2(antennas, grid));

	displayAntinodes(grid, allAntinodes);

	std::cout << Str(allAntinodes.size()) << std::endl;
}