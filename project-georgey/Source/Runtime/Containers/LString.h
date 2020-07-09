#pragma once

#include <string>
#include <vector>

class LString
{
public:
	static std::vector<std::string> SeperateStringByChar(std::string str, char c, bool removeZeroLength = true);

	static unsigned int HexStringToInt(std::string s);

	static unsigned int HexCharToInt(char c);

	static std::string GetFileLocation(const std::string fileName);

	static std::string GetFileName(const std::string fileName);
};