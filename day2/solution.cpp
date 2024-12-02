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

std::string VectorToString(std::vector<int> list)
{
	std::string res = "";

	for (int j = 0; j < list.size(); j++)
	{
		res += std::to_string(list[j]) + " ";
	}

	return res;
}

std::string VectorToString(std::vector<int> list, int badIndex)
{
	std::string res = "";

	for (int j = 0; j < list.size(); j++)
	{
		if (j == badIndex) {
			res += "["+std::to_string(list[j])+"]" + " ";
		}
		else {
			res += std::to_string(list[j]) + " ";
		}
	}

	return res;
}

void PrintVecotr(std::vector<std::vector<int>> listOfLists)
{
	for (int i = 0; i < listOfLists.size(); i++)
	{
		std::cout << VectorToString(listOfLists[i]) << std::endl;
	}
}

bool IsReportSafe(std::vector<int> nums, int& badIndex)
{
	bool increasing = false;
	bool decreasing = false;
	bool sequenceToSet = true;
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
			if (absDif < 1 || absDif > 3)
			{
				//std::cout << "'" + VectorToString(nums) + "' report unsafe. The dif between '" + std::to_string(nums[i-1]) + "' and '" + std::to_string(nums[i]) + "' is '" + std::to_string(dif) + "' and is too much." << std::endl;

				badIndex = i;
				return false;
			}
		}
		else
		{
			if (increasing && dif < 0) {
				//std::cout << "'" + VectorToString(nums) + "' report unsafe. Sequence increasing but the dif between '" + std::to_string(nums[i - 1]) + "' and '" + std::to_string(nums[i]) + "' is '" + std::to_string(dif) + "' and is negative." << std::endl;
			}

			if (decreasing && dif > 0) {
				//std::cout << "'" + VectorToString(nums) + "' report unsafe. Sequence decreasing but the dif between '" + std::to_string(nums[i - 1]) + "' and '" + std::to_string(nums[i]) + "' is '" + std::to_string(dif) + "' and is positive." << std::endl;
			}

			badIndex = i;
			return false;
		}
	}
	return true;
}

bool IsReportSafe(std::vector<int> nums) {
	int ignore = 0;
	return IsReportSafe(nums, ignore);
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
		if (IsReportSafe(nums))
		{
			safeReports.push_back(nums);
		}
	}

	std::cout << "Number of safe reports is: " + std::to_string(safeReports.size()) << std::endl;

	//PrintVecotr(safeReports);
}


//
//\033[31m:Starts red text.
//\033[32m:Starts green text.
//\033[34m:Starts blue text.
//\033[0m:Resets the text color to default.
void ToCoutGreen(std::string txt) {
	std::cout << "\033[32m" << txt << "\033[0m";
}

void ToCoutRed(std::string txt) {
	std::cout << "\033[31m" << txt << "\033[0m";
}

void ToCoutRedVectorWithBadIndex(std::vector<int> list, int badIndex) {
	for (int j = 0; j < list.size(); j++)
	{
		if (j == badIndex) {
			std::string txt = "[" + std::to_string(list[j]) + "]";
			std::cout << "\033[31m" << txt << "\033[0m";
		}
		else {
			std::string txt = std::to_string(list[j]);
			std::cout << txt;
		}

		if (j != list.size() - 1) {
			std::cout << " ";
		}
	}
}

void day2::Run2()
{
	std::vector<std::string> lines = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day2\\input.txt");
	//std::vector<std::string> lines = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day2\\sample.txt");
	std::vector<std::vector<int>> safeReports;
	std::vector<std::vector<int>> unsafeReports;
	std::cout << "'" + std::to_string(lines.size()) + "' total reports" << std::endl;

	for (int i = 0; i < lines.size(); i++)
	{
		std::string line = lines[i];

		std::vector<int> nums = stringToInts(line);
		int badIntex;
		if (IsReportSafe(nums, badIntex))
		{
			//std::cout << "'" + VectorToString(nums) + "' report safe." << std::endl;
			ToCoutGreen("[+]");
			std::cout << VectorToString(nums) << std::endl;

			safeReports.push_back(nums);
		}
		else 
		{
			std::vector<int> otion1 = nums;
			otion1.erase(otion1.begin() + badIntex);

			//std::cout << "'"+ VectorToString(nums) + "' report unsafe. trying to remove '"+ std::to_string(nums[badIntex]) + "' to see if '" + VectorToString(otion1) +"' is safe." << std::endl;

			if (IsReportSafe(otion1)) {
				//std::cout << "'" + VectorToString(otion1) + "' report is now safe." << std::endl;
				//std::cout << "[/]'" + VectorToString(nums, badIntex) + "'" << std::endl;
				ToCoutGreen("[+]");
				ToCoutRedVectorWithBadIndex(nums, badIntex);
				std::cout << " --> option1" << std::endl;

				safeReports.push_back(otion1);
				continue;
			}


			// The fix could be to remove the previous number
			std::vector<int> otion2 = nums;
			otion2.erase(otion2.begin() + badIntex-1);

			//std::cout << "'" + VectorToString(otion1) + "' was still unsafe. trying to remove '" + std::to_string(nums[badIntex-1]) + "' isntaed to see if '" + VectorToString(otion2) + "' is safe." << std::endl;

			if (IsReportSafe(otion2)) {

				//std::cout << "[/]'" + VectorToString(nums, badIntex-1) + "'" << std::endl;

				ToCoutGreen("[+]");
				ToCoutRedVectorWithBadIndex(nums, badIntex-1);
				std::cout << " --> option2" << std::endl;

				safeReports.push_back(otion2);
				continue;
			}


			// The fix could be that the increase / decrease from the 1st set of nums is good but bad for all the rest.
			std::vector<int> option3 = nums;
			option3.erase(option3.begin() + 0); // remove 1st item to check if seq works and its broken just by wrong direction


			if(IsReportSafe(option3)) {

				//std::cout << "[/]'" + VectorToString(nums, 0) + "'" << std::endl;

				ToCoutGreen("[+]");
				ToCoutRedVectorWithBadIndex(nums, 0);
				std::cout << " --> option3" << std::endl;

				safeReports.push_back(option3);
				continue;
			}
			
			//std::cout << "'" + VectorToString(otion2) + "' was still unsafe. Report '" + VectorToString(nums) + "' cannot be made safe." << std::endl;
			//std::cout << "[-]'" + VectorToString(nums, badIntex) + "'" << std::endl;

			ToCoutRed("[-]");
			std::cout << VectorToString(nums) << std::endl;

			unsafeReports.push_back(nums);
		}
	}


	std::cout << "Number of safe reports is: " + std::to_string(safeReports.size()) << std::endl;

	//PrintVecotr(safeReports);
	
	std::cout << "Number of unsafe reports is: " + std::to_string(unsafeReports.size()) << std::endl;
	//PrintVecotr(unsafeReports);


}


void day2::Run2b() {
	std::vector<std::string> lines = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day2\\input.txt");
	//std::vector<std::string> lines = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day2\\sample.txt");
	std::vector<std::vector<int>> safeReports;
	std::vector<std::vector<int>> unsafeReports;

	for (int i = 0; i < lines.size(); i++)
	{
		std::string line = lines[i];
		std::vector<int> nums = stringToInts(line);
		
		for (int j = 0; j < nums.size(); j++)
		{
			std::vector<int> option1 = nums;
			option1.erase(option1.begin() + j);

			if (IsReportSafe(option1)) {
				safeReports.push_back(nums);
				std::cout << "[+]'" + VectorToString(nums, j) + "'" << std::endl;

				break;
			}
		}

		unsafeReports.push_back(nums);

	}

	std::cout << "Number of safe reports is: " + std::to_string(safeReports.size()) << std::endl;

	//PrintVecotr(safeReports);

	std::cout << "Number of unsafe reports is: " + std::to_string(unsafeReports.size()) << std::endl;
	//PrintVecotr(unsafeReports);
}