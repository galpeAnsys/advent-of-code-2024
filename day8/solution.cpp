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

void day8::Run() 
{
	//std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day8\\sample1.txt");
	std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day8\\input.txt");

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
	std::unordered_set<pos> allAntinodes;

	for (auto& an : antennas)
	{

		std::unordered_set<pos> antinodes;
		for (size_t i = 0; i < an.second.size(); i++)
		{
			for (size_t j = i+1; j < an.second.size(); j++)
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
		//allAntinodes.insert(allAntinodes.end(), antinodes.begin(), antinodes.end());

		std::cout << "[" + std::to_string(an.first) + "] " + vectorToString(an.second) + " >> " + setToString(antinodes) << std::endl;


		
	}
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


	std::cout << Str(allAntinodes.size()) << std::endl;
}


void day8::Run2() {}