#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include <unordered_set>
#include <unordered_map>
#include <optional>
#include "../FileHelper.h"
#include "../Helpers/pos.h"
#include "solution.h"

std::string vectorToString(std::vector<std::string> list) {
	std::string res;
	for (auto& p : list)
	{
		res += p;
	}

	return res;
}

int findLastNonDotIndex(const std::vector<std::string>& vec, int startFrom) {
	for (int i = startFrom; i >= 0; --i) {
		if (vec[i] != ".") {
			return i;
		}
	}
	throw std::exception("could not find '.'");
}

int findLastNonDotIndex(const std::vector<std::string>& vec) {
	return findLastNonDotIndex(vec, vec.size() - 1);
}

class startAndEnd {
public:
	int start;
	int end;

	startAndEnd(int s, int e) : start(s), end(e) {};
};

class fileBlock {
public:
	std::string block;
	startAndEnd se;

	fileBlock(std::string b, startAndEnd se) : block(b), se(se) {};
};

class memodyBlocks {
public: 
	std::vector<std::string> blocks;
	std::unordered_map<int, std::vector<startAndEnd>> gaps;
	std::vector<fileBlock> fileBlocks;
	std::vector<fileBlock> gapBlocks;
};

memodyBlocks parseInput(std::string& line) {
	memodyBlocks res;
	for (size_t i = 0; i < line.size(); i++)
	{
		auto& block = line[i];
		int fileLength = std::stoi(std::string(1, block));
		if (i % 2 != 0) { //free space
			int start = res.blocks.size();
			for (size_t j = 0; j < fileLength; j++)
			{
				res.blocks.push_back(".");
			}
			int end = res.blocks.size() - 1;
			res.gaps[fileLength].push_back(startAndEnd(start, end));
			res.gapBlocks.push_back(fileBlock(std::string(fileLength, '.'), startAndEnd(start, end)));
		}
		else { //file block
			int id = i / 2;
			int start = res.blocks.size();
			std::string block;
			for (size_t j = 0; j < fileLength; j++)
			{
				res.blocks.push_back(Str(id));
				block += Str(id);
			}
			int end = res.blocks.size() - 1;
			res.fileBlocks.push_back(fileBlock(block,  startAndEnd(start, end)));
		}
	}
	return res;
}

std::vector<std::string> compressMemory(std::vector<std::string>& momoryBlocks) {
	std::vector<std::string> copyMemBlocks(momoryBlocks);
	int tail = findLastNonDotIndex(copyMemBlocks);

	for (size_t i = 0; i < copyMemBlocks.size(); i++)
	{
		if (i >= tail) break;
		auto& block = copyMemBlocks[i];
		if (block == ".") {
			block = copyMemBlocks[tail];
			copyMemBlocks[tail] = ".";

			tail = findLastNonDotIndex(copyMemBlocks, tail);
			//std::cout << vectorToString(copyMemBlocks) << std::endl;
		}
	}

	return copyMemBlocks;
}

long long solveChecksum(std::vector<std::string>& memBlocks) {
	long long checksum = 0;
	for (size_t i = 0; i < memBlocks.size(); i++)
	{
		auto& block = memBlocks[i];
		if (block == ".") continue;


		checksum += std::stoi(block) * i;
	}

	return checksum;
}

void day9::Run() {
	//std::string line = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day9\\sample1.txt")[0];
	std::string line = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day9\\input.txt")[0];

	memodyBlocks momoryBlocks = parseInput(line);

	std::cout << vectorToString(momoryBlocks.blocks) << std::endl;
	std::cout << "---------------------------" << std::endl;

	std::vector<std::string> copyMemBlocks = compressMemory(momoryBlocks.blocks);

	std::cout << vectorToString(copyMemBlocks) << std::endl;
	std::cout << "---------------------------" << std::endl;

	long long checksum = solveChecksum(copyMemBlocks);
	std::cout << std::to_string(checksum) << std::endl;

};


std::optional<std::pair<fileBlock, int>> firstGapGreaterEqualTo(int size, std::vector<fileBlock> gaps, startAndEnd seOfBlock) {
	for (size_t i = 0; i < gaps.size(); i++)
	{
		auto& gap = gaps[i];
		if (gap.se.start >= seOfBlock.start) return std::nullopt; //gap is further than memory already is.
		if (gap.block.size() >= size) return std::make_pair(gap, i);
	}
	return std::nullopt;
}

std::vector<std::string> compressMemory2(memodyBlocks momoryBlocks) {
	//std::vector<std::string> copyMemBlocks(momoryBlocks.blocks);

	int maxGapSize = 0;
	for (size_t i = 0; i < momoryBlocks.gapBlocks.size(); i++)
	{
		auto& gap = momoryBlocks.gapBlocks[i];
		if (gap.block.size() > maxGapSize) maxGapSize = gap.block.size();
	}

	for (size_t i = momoryBlocks.fileBlocks.size() - 1; i << momoryBlocks.fileBlocks.size() >  0; i--)
	{
		auto& lastBlock = momoryBlocks.fileBlocks[i];
		int blockSize = lastBlock.se.end - lastBlock.se.start + 1;

		if (blockSize > maxGapSize) continue; // too big wont fit anywhere

		auto gap = firstGapGreaterEqualTo(blockSize, momoryBlocks.gapBlocks, lastBlock.se);
		if (!gap) continue; //no gaps left of this size;

		std::string val;
		for (size_t i = lastBlock.se.start; i <= lastBlock.se.end; i++)
		{
			val = momoryBlocks.blocks[i];
			momoryBlocks.blocks[i] = ".";
		}

		int s1 = gap->first.se.start;
		int e1 = s1 + blockSize;
		for (size_t i = s1; i < e1; i++)
		{
			momoryBlocks.blocks[i] = val;
		}

		auto& gapToEdit = momoryBlocks.gapBlocks[gap->second];
		for (size_t i = 0; i < blockSize; i++)
		{
			gapToEdit.block.erase(gapToEdit.block.begin());
			gapToEdit.se.start++;
		}
		//std::cout << vectorToString(momoryBlocks.blocks) << std::endl;
	}

	return momoryBlocks.blocks;
}

void day9::Run2() {
	//std::string line = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day9\\sample2.txt")[0];
	std::string line = ReadInput("D:\\ANSYSDev\\Learning\\C++\\AoC24\\day9\\input.txt")[0];

	memodyBlocks momoryBlocks = parseInput(line);

	std::cout << vectorToString(momoryBlocks.blocks) << std::endl;
	std::cout << "---------------------------" << std::endl;

	std::vector<std::string> copyMemBlocks = compressMemory2(momoryBlocks);

	std::cout << vectorToString(copyMemBlocks) << std::endl;
	std::cout << "---------------------------" << std::endl;

	long long checksum = solveChecksum(copyMemBlocks);
	std::cout << std::to_string(checksum) << std::endl;
};
