#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include "../FileHelper.h"
#include "solution.h"
#include "solution.h"

std::regex ptrnXmasLtr(R"(XMAS)");
std::regex ptrnXmasRtl(R"(SAMX)");


// NOTES: I could probably put the whole string into a grid instead of line by line. 
// Then look for 'X' and check all 6 directions of the grid to see if it spells out 'XMAS'

std::string str(int i) {
	return std::to_string(i);
}

bool CheckInBounds(std::vector<std::string> grid, std::vector<std::pair<int, int>> pos) {
	int rows = grid.size();
	int cols = grid[0].size();
	char r1 = pos[1].first, r2 = pos[2].first, r3 = pos[3].first;
	char c1 = pos[1].second, c2 = pos[2].second, c3 = pos[3].second;

	if (r1 < 0 || r2 < 0 || r3 < 0 ||
		r1 > rows || r2 > rows || r3 > rows) {
		return false;
	}

	if (c1 < 0 || c2 < 0 || c3 < 0 ||
		c1 > cols || c2 > cols || c3 > cols) {
		return false;
	}

	return true;
}

bool CheckXmas(std::vector<std::string> grid, std::vector<std::pair<int, int>> pos, std::string dir)
{
	if (!CheckInBounds(grid, pos)) return false;

	char m = grid[pos[1].first][pos[1].second];
	char a = grid[pos[2].first][pos[2].second];
	char s = grid[pos[3].first][pos[3].second];

	if (m != 'M' || a != 'A' || s != 'S') {
		return false;
	}
	int r = pos[1].first;
	int c = pos[1].second;
	std::cout << "At [" + str(r) + ", " + str(c) + "] "+dir+" found: X" + m + a + s << std::endl;

	return true;
}

bool CheckNorth(std::vector<std::string> grid, int r, int c) {
	std::vector<std::pair<int, int>> pos = { {r, c}, {r - 1, c}, {r - 2, c}, {r - 3, c} };
	return CheckXmas(grid, pos, "North");
}

bool CheckNorthEast(std::vector<std::string> grid, int r, int c) {
	std::vector<std::pair<int, int>> pos = { {r, c}, {r - 1, c + 1}, {r - 2, c + 2}, {r - 3, c + 3} };
	return CheckXmas(grid, pos, "North East");
}

bool CheckEast(std::vector<std::string> grid, int r, int c) {
	std::vector<std::pair<int, int>> pos = { {r, c}, {r, c + 1}, {r, c + 2}, {r, c + 3} };
	return CheckXmas(grid, pos, "East");
}

bool CheckSouthEast(std::vector<std::string> grid, int r, int c) {
	std::vector<std::pair<int, int>> pos = { {r, c}, {r + 1, c + 1}, {r + 2, c + 2}, {r + 3, c + 3} };
	return CheckXmas(grid, pos, "South East");
}

bool CheckSouth(std::vector<std::string> grid, int r, int c) {
	std::vector<std::pair<int, int>> pos = { {r, c}, {r + 1, c}, {r + 2, c}, {r + 3, c} };
	return CheckXmas(grid, pos, "South");
}

bool CheckSouthWest(std::vector<std::string> grid, int r, int c) {
	std::vector<std::pair<int, int>> pos = { {r, c}, {r + 1, c - 1}, {r + 2, c - 2}, {r + 3, c - 3} };
	return CheckXmas(grid, pos, "South West");
}

bool CheckWest(std::vector<std::string> grid, int r, int c) {
	std::vector<std::pair<int, int>> pos = { {r, c}, {r, c - 1}, {r, c - 2}, {r, c - 3} };
	return CheckXmas(grid, pos, "West");
}

bool CheckNorthWest(std::vector<std::string> grid, int r, int c) {
	std::vector<std::pair<int, int>> pos = { {r, c}, {r - 1, c - 1}, {r - 2, c - 2}, {r - 3, c - 3} };
	return CheckXmas(grid, pos, "North West");
}

int TryFindXmas(std::vector<std::string> grid, int r, int c) {
	// 8 possible direactions: N, NE, E, SE, S, SW, W, NW
	int xmasCount = 0;
	if (grid[r][c] != 'X') return 0;
	if(CheckNorth(grid, r, c)) xmasCount++;
	if(CheckNorthEast(grid, r, c)) xmasCount++;
	if(CheckEast(grid, r, c)) xmasCount++;
	if(CheckSouthEast(grid, r, c)) xmasCount++;
	if(CheckSouth(grid, r, c)) xmasCount++;
	if(CheckSouthWest(grid, r, c)) xmasCount++;
	if(CheckWest(grid, r, c)) xmasCount++;
	if (CheckNorthWest(grid, r, c)) xmasCount++;

	return xmasCount;
}

void day4::Run() {
	//std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day4\\sample3.txt");
	std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day4\\input.txt");

	int xmasCount = 0;
	for (int r = 0; r < grid.size(); r++)
	{
		auto& row = grid[r];
		for (int c = 0; c < row.size(); c++) {
			auto& col = row[c];
			xmasCount += TryFindXmas(grid, r, c);
		}
	}

	std::cout << str(xmasCount) << std::endl;

}

void day4::Run2() {
}