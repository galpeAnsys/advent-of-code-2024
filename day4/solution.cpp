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

	for (auto& p : pos) {
		int r = p.first;
		int c = p.second;

		if (r < 0 || r >= rows ||
			c < 0 || c >= cols) 
		{
			return false;
		}
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

/*
M-M
-A-
S-S
*/
int TryFindXMas(std::vector<std::string> grid, int r, int c) {
	int xmasCount = 0;
	if (grid[r][c] != 'A') return 0;

	std::vector<std::pair<int, int>> pos = { {r, c}, {r - 1, c - 1}, {r - 1, c + 1}, {r + 1, c - 1}, {r + 1, c + 1} };

	if (!CheckInBounds(grid, pos)) return 0;

	char topLeft = grid[pos[1].first][pos[1].second];
	char topRight = grid[pos[2].first][pos[2].second];
	char center = grid[pos[0].first][pos[0].second];
	char bottomLeft = grid[pos[3].first][pos[3].second];
	char bottomRight = grid[pos[4].first][pos[4].second];

	std::string mas1{ topLeft, center, bottomRight };
	std::string mas2{ topRight, center, bottomLeft };

	if (mas1 != "MAS" && mas1 != "SAM" ||
		mas2 != "MAS" && mas2 != "SAM")
	{
		return 0;
	}

	std::cout << "At [" + str(r) + ", " + str(c) + "] " + " found:" << std::endl;
	std::cout << std::string{ topLeft,'-',topRight } << std::endl;
	std::cout << std::string{ '-', center, '-' } << std::endl;
	std::cout << std::string{ bottomLeft, '-', bottomRight } << std::endl;

	return 1;
}

void day4::Run() {
	std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day4\\sample4.txt");
	//std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day4\\input.txt");

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
	//std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day4\\sample5.txt");
	std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day4\\input.txt");

	int xmasCount = 0;
	for (int r = 0; r < grid.size(); r++)
	{
		auto& row = grid[r];
		for (int c = 0; c < row.size(); c++) {
			auto& col = row[c];
			xmasCount += TryFindXMas(grid, r, c);
		}
	}

	std::cout << str(xmasCount) << std::endl;
}