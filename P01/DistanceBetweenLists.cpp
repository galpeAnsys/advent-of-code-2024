#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <algorithm>
#include "DistanceBetweenLists.h"
#include "../FileHelper.h"
#include <unordered_map>



std::tuple<int, int> splitStringToInts(const std::string& str) {
	int num1, num2;
	std::stringstream ss;

	ss.str(str);
	ss >> num1 >> num2;
	return std::make_tuple(num1, num2);
}


void day1::Run()
{
	std::vector<std::string> lines = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\P01\\input.txt");
	std::vector<int> leftList(lines.size());
	std::vector<int> rightList(lines.size());

	for (int i = 0; i < lines.size(); i++)
	{
		std::string line = lines[i];
		auto [num1, num2] = splitStringToInts(line);
		leftList[i] = num1;
		rightList[i] = num2;
	}

	std::cout << leftList[0] << std::endl;
	std::cout << rightList[0] << std::endl;

	// Sort the vector in ascending order
	std::sort(leftList.begin(), leftList.end());
	std::sort(rightList.begin(), rightList.end());

	std::cout << leftList[0] << std::endl;
	std::cout << rightList[0] << std::endl;

	std::vector<int> difs(lines.size());
	int difSum = 0;

	for (int i = 0; i < lines.size(); i++)
	{
		int left = leftList[i];
		int right = rightList[i];
		int dif = std::abs(left - right);

		difs[i] = dif;
		difSum += dif;
	}

	std::cout << "the dif sum is: " + std::to_string(difSum) << std::endl;

}

void day1::Run2()
{
	std::vector<std::string> lines = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\P01\\input.txt");
	std::vector<int> leftList(lines.size());
	std::unordered_map<int, int> rightList;

	for (int i = 0; i < lines.size(); i++)
	{
		std::string line = lines[i];
		auto [num1, num2] = splitStringToInts(line);
		leftList[i] = num1;
		rightList[num2] += 1; // Increment the value by 1 if key exists (or if not, it will set to 1)
	}

	std::cout << "the rightList sum is: " + std::to_string(rightList.size()) << std::endl;

	int64_t sum = 0;

	for (int i = 0; i < lines.size(); i++)
	{
		int left = leftList[i];

		sum += left * rightList[left];
	}

	std::cout << "the sum is: " + std::to_string(sum) << std::endl;

}
