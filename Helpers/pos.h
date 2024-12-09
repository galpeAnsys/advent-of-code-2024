#pragma once

class pos {
public:
	int r, c;

	// Constructor
	pos();
	pos(int row, int col);

	// Overload equality operator
	bool operator==(const pos& other) const {
		return r == other.r && c == other.c;
	}

	// Member functions
	void display() const;
	std::string toString() const;
};

// std::hash specialization for `hash<pos>`
namespace std {
	template<>
	struct hash<pos> {
		size_t operator()(const pos& p) const {
			return std::hash<int>()(p.r) ^ (std::hash<int>()(p.c) << 1);
		}
	};
}