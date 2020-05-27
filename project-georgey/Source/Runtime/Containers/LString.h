#pragma once

#include <string>
#include <vector>

class LString
{
public:
	static std::vector<std::string> SeperateStringByChar(std::string str, char c, bool removeZeroLength = true);

	static std::string GetFileLocation(const std::string fileName);

	static std::string GetFileName(const std::string fileName);
};