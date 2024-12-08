#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include <unordered_set>
#include "../FileHelper.h"
#include "solution.h"


// Function to split a string into one number and a list of numbers
std::pair<unsigned long long, std::vector<int>> splitNumbers(std::string input) {
    // Split the input string into the leading number and the rest
    size_t colonPos = input.find(':');
    if (colonPos == std::string::npos) {
        throw std::invalid_argument("Invalid input format, ':' not found.");
    }

    // Get the leading number
    unsigned long long leadingNumber = std::stoull(input.substr(0, colonPos));

    // Extract the rest of the numbers from the part after ':'
    std::string numbersPart = input.substr(colonPos + 2);
    std::vector<int> numbers;
    size_t pos = 0;
    size_t spacePos;
    while ((spacePos = numbersPart.find(' ', pos)) != std::string::npos) {
        numbers.push_back(std::stoi(numbersPart.substr(pos, spacePos - pos)));
        pos = spacePos + 1;
    }
    // Add the last number
    if (pos < numbersPart.size()) {
        numbers.push_back(std::stoi(numbersPart.substr(pos)));
    }

    return { leadingNumber, numbers };
}

enum Op
{
    Add, Multiply, Concat
};

class Equation {
public:
    unsigned long long testValue;
    std::vector<int> nums;
    std::vector<Op> ops;
    unsigned long long solution;

    void solve() {
        if (nums.size() - 1 != ops.size()) throw std::exception("Cannot solve. not the right number of Operations for the Numbers");

        unsigned long long result = nums[0];
        for (size_t i = 1; i < nums.size(); i++)
        {
            Op operation = ops[i - 1];
            int num = nums[i];
            if (operation == Op::Add) {
                result += num;
            }
            if (operation == Op::Multiply) {
                result *= num;
            }

            if (operation == Op::Concat) {
                result = std::stoull(Str(result) + Str(num));
            }
        }

        solution = result;
    }

    void ToCoutGreen(std::string txt) {
        std::cout << "\033[32m" << txt << "\033[0m";
    }

    void ToCoutRed(std::string txt) {
        std::cout << "\033[31m" << txt << "\033[0m";
    }

    void display() {
        std::string result = Str(nums[0]);
        for (size_t i = 1; i < nums.size(); i++)
        {
            Op operation = ops[i - 1];
            std::string num = Str(nums[i]);
            if (operation == Op::Add) {
                result += "+" + num; 
            }
            if (operation == Op::Multiply) {
                result += "*" + num;
            }
            if (operation == Op::Concat) {
                result += "||" + num;
            }
        }

        std::string str(result + " = " + Str(solution) + "[" + Str(testValue) + "]");
        if (solution == testValue) {
            ToCoutGreen(str);
            std::cout << std::endl;
        }
        else {
            /*if (nums.size() <= 3) {
                ToCoutRed(str);
                std::cout << std::endl;
            }*/
        }
    }
};

bool IsEquationValid(std::pair<unsigned long long, std::vector<int>> equation) {
    unsigned long long testValue = equation.first;
    std::vector<int> numbers = equation.second;

    Equation eq; 
    eq.testValue = testValue;
    eq.nums = numbers;


    std::vector<Equation> possibleEquations;

    for (size_t i = 0; i < numbers.size()-1; i++)
    {
        std::vector<Equation> copy(possibleEquations);
        for (Equation& e : possibleEquations) {
            e.ops.push_back(Op::Add);
        }

        for (Equation& e : copy) {
            e.ops.push_back(Op::Multiply);
        }
        possibleEquations.insert(possibleEquations.end(), copy.begin(), copy.end());

        if (possibleEquations.size() == 0) { // 1st loop
            Equation e1(eq);
            e1.ops.push_back(Op::Add);
            possibleEquations.push_back(e1);
            Equation e2(eq);
            e2.ops.push_back(Op::Multiply);
            possibleEquations.push_back(e2);
        }
    }

    for (Equation& e : possibleEquations) {
        e.solve();
        e.display();
    }

    for (Equation& e : possibleEquations) {
        if (e.testValue == e.solution) return true;
    }
    return false;
}

void day7::Run() {
	//std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day7\\sample2.txt");
	std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day7\\input.txt");

    try {
        unsigned long long sum = 0;
        for (auto& line : grid) {
            auto equation = splitNumbers(line);
            if (IsEquationValid(equation)) {
                sum += equation.first;
            }
        }
        std::cout << Str(sum) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

	//std::cout << Str(guard.routeDistinct.size()) << std::endl;
}

//
//
//// two nums... 
//if (testValue == numbers[0] + numbers[1]) return true;
//if (testValue == numbers[0] * numbers[1]) return true;
//
//return false;
//
//// three nums
//if (testValue == numbers[0] + numbers[1] + numbers[2]) return true;
//
//if (testValue == numbers[0] * numbers[1] + numbers[2]) return true;
//if (testValue == numbers[0] + numbers[1] * numbers[2]) return true;
//
//if (testValue == numbers[0] * numbers[1] * numbers[2]) return true;
//
//return false;
//
//// four nums
//
//if (ts == n[0] + n[1] + n[2] + n[3]) return true;
//if (ts == n[0] * n[1] + n[2] + n[3]) return true;
//
//if (ts == n[0] + n[1] * n[2] + n[3]) return true;
//if (ts == n[0] * n[1] * n[2] + n[3]) return true;
//
//if (ts == n[0] + n[1] + n[2] * n[3]) return true;
//if (ts == n[0] * n[1] + n[2] * n[3]) return true;
//if (ts == n[0] + n[1] * n[2] * n[3]) return true;
//if (ts == n[0] * n[1] * n[2] * n[3]) return true;
//
//
//// five
//if (ts == n[0] + n[1] + n[2] + n[3] + n[4]) return true;
//if (ts == n[0] * n[1] + n[2] + n[3] + n[4]) return true;
//
//if (ts == n[0] + n[1] * n[2] + n[3] + n[4]) return true;
//if (ts == n[0] * n[1] * n[2] + n[3] + n[4]) return true;
//
//if (ts == n[0] + n[1] + n[2] * n[3] + n[4]) return true;
//if (ts == n[0] * n[1] + n[2] * n[3] + n[4]) return true;
//if (ts == n[0] + n[1] * n[2] * n[3] + n[4]) return true;
//if (ts == n[0] * n[1] * n[2] * n[3] + n[4]) return true;
//
//if (ts == n[0] + n[1] + n[2] + n[3] * n[4]) return true;
//if (ts == n[0] * n[1] + n[2] + n[3] * n[4]) return true;
//
//if (ts == n[0] + n[1] * n[2] + n[3] * n[4]) return true;
//if (ts == n[0] * n[1] * n[2] + n[3] * n[4]) return true;
//
//if (ts == n[0] + n[1] + n[2] * n[3] * n[4]) return true;
//if (ts == n[0] * n[1] + n[2] * n[3] * n[4]) return true;
//if (ts == n[0] + n[1] * n[2] * n[3] * n[4]) return true;
//if (ts == n[0] * n[1] * n[2] * n[3] * n[4]) return true;
//
//// Operations + and * 
//
//// num of operations == numbers.size()-1


bool IsEquationValid2(std::pair<unsigned long long, std::vector<int>> equation) {
    unsigned long long testValue = equation.first;
    std::vector<int> numbers = equation.second;

    Equation eq;
    eq.testValue = testValue;
    eq.nums = numbers;

    std::vector<Equation> possibleEquations;

    for (size_t i = 0; i < numbers.size() - 1; i++)
    {
        std::vector<Equation> copy1(possibleEquations);
        std::vector<Equation> copy2(possibleEquations);
        for (Equation& e : possibleEquations) {
            e.ops.push_back(Op::Add);
        }

        for (Equation& e : copy1) {
            e.ops.push_back(Op::Multiply);
        }
        
        for (Equation& e : copy2) {
            e.ops.push_back(Op::Concat);
        }

        possibleEquations.insert(possibleEquations.end(), copy1.begin(), copy1.end());
        possibleEquations.insert(possibleEquations.end(), copy2.begin(), copy2.end());

        if (possibleEquations.size() == 0) { // 1st loop
            Equation e1(eq);
            e1.ops.push_back(Op::Add);
            possibleEquations.push_back(e1);
            Equation e2(eq);
            e2.ops.push_back(Op::Multiply);
            possibleEquations.push_back(e2);
            Equation e3(eq);
            e3.ops.push_back(Op::Concat);
            possibleEquations.push_back(e3);
        }
    }

    for (Equation& e : possibleEquations) {
        e.solve();
        e.display();
    }

    for (Equation& e : possibleEquations) {
        if (e.testValue == e.solution) return true;
    }
    return false;
}

void day7::Run2() {
    //std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day7\\sample1.txt");
    std::vector<std::string> grid = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day7\\input.txt");

    try {
        unsigned long long sum = 0;
        for (auto& line : grid) {
            auto equation = splitNumbers(line);
            if (IsEquationValid2(equation)) {
                sum += equation.first;
            }
        }
        std::cout << Str(sum) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

