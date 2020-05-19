#pragma once

#include <string>
#include <vector>

class LString
{
public:
	static std::vector<std::string> SeperateStringByChar(std::string str, char c, bool removeZeroLength = true);
};