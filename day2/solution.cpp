#include "solution.h"
#include <string>
#include <vector>
#include <sstream>
#include "../FileHelper.h"
#include <iostream>

std::vector<int> stringToInts(std::string line) {
	std::vector<int> numbers;
	std::istringstream stream(line);
	int num = 0;

	while (stream >> num) {
		numbers.push_back(num);
	}

	return numbers;
}

void day2::Run()
{
	std::vector<std::string> lines = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day2\\input.txt");
	//std::vector<std::string> lines = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day2\\sample.txt");
	std::vector<std::vector<int>> safeReports; 

	for (int i = 0; i < lines.size(); i++)
	{
		std::string line = lines[i];

		std::vector<int> nums = stringToInts(line);

		int preDif = 0;
		bool increasing = false;
		bool decreasing = false;
		bool sequenceToSet = true;
		bool safeReport = false;
		// lists of 1 number? 
		for (int i = 1; i < nums.size(); i++)
		{
			int pre = nums[i - 1];
			int num = nums[i];
			int dif = num - pre;

			if (sequenceToSet && dif > 0) 
			{
				increasing = true;
				sequenceToSet = false;
			}
			else if (sequenceToSet && dif < 0) 
			{
				decreasing = true;
				sequenceToSet = false;
			}

			// if increasing or decreasing
			if ((increasing && dif > 0) ||
				decreasing && dif < 0) 
			{
				int absDif = std::abs(dif);
				//if gradual
				if (absDif >= 1 && absDif <= 3)
				{
					safeReport = true;
				}
				else 
				{
					safeReport = false;
					break;
				}
			}
			else 
			{
				safeReport = false;
				break;
			}
		}

		if (safeReport)
		{
			safeReports.push_back(nums);
		}
	}

	std::cout << "Number of safe reports is: " + std::to_string(safeReports.size()) << std::endl;

	/*for (int i = 0; i < safeReports.size(); i++)
	{
		std::vector<int> report = safeReports[i];
		std::string repStr = "";

		for (int j = 0; j < report.size(); j++)
		{
			repStr += std::to_string(report[j]) + " ";
		}
		std::cout << repStr << std::endl;
	}*/

}

void day2::Run2()
{
}
