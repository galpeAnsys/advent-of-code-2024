﻿// AoC24.cpp : Defines the entry point for the application.
//

#include "AoC24.h"
#include "P01/DistanceBetweenLists.h"
#include "day2/solution.h"
#include "day3/solution.h"
#include "day4/solution.h"
#include "day6/solution.h"
#include "day7/solution.h"
#include "day8/solution.h"
#include "day9/solution.h"

using namespace std;

int main()
{
	try {
		cout << "Advent of Code 2024" << endl;

		//day1::Run();
		//day1::Run2();
		//day2::Run();
		//day2::Run2();
		//day3::Run();
		//day3::Run2();
		//day4::Run();
		//day4::Run2();
		//day6::Run();
		//day7::Run();
		//day7::Run2();
		//day8::Run();
		//day8::Run2();
		//day9::Run();
		day9::Run2();

		return 0;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}
