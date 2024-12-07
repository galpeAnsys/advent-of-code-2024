#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include <unordered_set>
#include "../FileHelper.h"
#include "solution.h"


std::string Str(int i) {
	return std::to_string(i);
}

enum class Dir {
	NONE, UP, RIGHT, DOWN, LEFT
};

class Pos {
public:
	int r;
	int c;

	Pos() : r(0), c(0) {}
	Pos(int row, int col) : r(row), c(col) {}

	// Overload equality operator
	bool operator==(const Pos& other) const {
		return r == other.r && c == other.c;
	}

	void Print() {
		std::cout << "(" << r << ", " << c << ")" << std::endl;
	}

	std::string ToStr() {
		return "(" + Str(r) + "," + Str(c) + ")";
	}
};

// Specialize std::hash for Point
namespace std {
	template<>
	struct hash<Pos> {
		size_t operator()(const Pos& p) const {
			return std::hash<int>()(p.r) ^ (std::hash<int>()(p.c) << 1);
		}
	};
}

class Guard {
private:
	std::vector<std::string> grid;
public:
	Pos pos;
	Dir dir;
	std::vector<Pos> route;
	std::unordered_set<Pos> routeDistinct;

	Guard(std::vector<std::string> inGrid) {
		grid = inGrid;
		pos = GetStartPos();
		switch (grid[pos.r][pos.c])
		{
		case '^':
			dir = Dir::UP;
			break;
		case '>':
			dir = Dir::RIGHT;
			break;
		case 'v':
			dir = Dir::DOWN;
			break;
		case '<':
			dir = Dir::LEFT;
			break;
		default:
			throw std::exception("failed to determine direction");
		}
		route.push_back(pos);
		routeDistinct.insert(pos);
	}

	Pos GetStartPos() {
		for (int r = 0; r < grid.size(); r++)
		{
			auto& row = grid[r];
			for (int c = 0; c < row.size(); c++) {
				auto& col = row[c];

				if (col == '^' || col == '>' || col == 'v' || col == '<') return Pos(r, c);
			}
		}
		throw std::exception("failed to find starting pos");
	}

	Pos Forward() {
		if (dir == Dir::UP) return Pos(pos.r - 1, pos.c);
		if (dir == Dir::RIGHT) return Pos(pos.r, pos.c + 1);
		if (dir == Dir::DOWN) return Pos(pos.r + 1, pos.c);
		if (dir == Dir::LEFT) return Pos(pos.r, pos.c - 1);
		throw std::exception("Failed to Forward");
	}

	bool InLab(Pos p) {
		int rows = grid.size();
		int cols = grid[0].size();

		if (p.r < 0 || p.r >= rows ||
			p.c < 0 || p.c >= cols)
		{
			return false;
		}

		return true;
	}

	bool InLab() {
		return InLab(pos);
	}

	void Turn90() {
		if (dir == Dir::UP) dir = Dir::RIGHT;
		else if (dir == Dir::RIGHT) dir = Dir::DOWN;
		else if (dir == Dir::DOWN) dir = Dir::LEFT;
		else if (dir == Dir::LEFT) dir = Dir::UP;
		else throw std::exception("Failed to turn");
	}

	bool TryMoveForward() {
		Pos possibleMove = Forward();

		if (!InLab(possibleMove)) {
			pos = possibleMove;
			return true;
		}

		char ahead = grid[possibleMove.r][possibleMove.c];
		if (ahead != '#') {
			pos = possibleMove;
			route.push_back(pos);
			routeDistinct.insert(pos);
			return true;
		}

		return false;
	}

	//could be unable to move
	void Move() {
		for (int i = 0; i < 4; i++)
		{
			if (TryMoveForward()) return;

			Turn90();
		}
		
		throw std::exception("Stuck in place");
	}
};



void day6::Run() {
	//std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day6\\sample1.txt");
	std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day6\\input.txt");

	Guard guard(grid);

	while (guard.InLab()) {
		guard.Move();
	}

	 std::cout << Str(guard.routeDistinct.size()) << std::endl;
}

void day6::Run2() {

}