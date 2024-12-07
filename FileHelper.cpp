#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileHelper.h"

std::vector<std::string> ReadInput(std::string inputPath) {
    //std::cerr << inputPath << std::endl;
    std::ifstream inputFile;

    inputFile.open(inputPath);
    if (!inputFile.is_open()) {
        //std::cerr << "Error: Could not open the file!" << std::endl;
        throw std::runtime_error("Error: Could not open the file " + inputPath);
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile, line)) {
        //std::cout << line << std::endl; // Print each line to the console
        lines.push_back(line); // Add each line to the vector
    }

    inputFile.close();
    return lines;
}


std::string Str(int i) {
    return std::to_string(i);
}

std::string Str(unsigned long long i) {
    return std::to_string(i);
}