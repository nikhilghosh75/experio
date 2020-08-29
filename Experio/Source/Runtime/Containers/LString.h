#pragma once

#include <string>
#include <vector>

class LString
{
public:
	static int CharToInt(char c);

	static std::string GetFileLocation(const std::string fileName);

	static std::string GetFileName(const std::string fileName);

	static unsigned int HexStringToInt(std::string s);

	static unsigned int HexCharToInt(char c);

	static bool IsAlpha(char c);
	static bool IsAlphaNumeric(char c);
	static bool IsLower(char c);
	static bool IsNumeric(char c);
	static bool IsUpper(char c);

	static std::vector<std::string> SeperateStringByChar(std::string str, char c, bool removeZeroLength = true);

	static float StringToFloat(std::string str);

	static int StringToInt(std::string str);
};