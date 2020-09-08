#pragma once

#include <string>
#include <vector>

class LString
{
public:
	constexpr static int CharToInt(char c);

	static std::string GetFileLocation(const std::string fileName);

	static std::string GetFileName(const std::string fileName);

	static unsigned int HexStringToInt(std::string s);

	static unsigned int HexCharToInt(char c);

	constexpr static bool IsAlpha(char c);
	constexpr static bool IsAlphaNumeric(char c);
	constexpr static bool IsLower(char c);
	constexpr static bool IsNumeric(char c);
	constexpr static bool IsUpper(char c);

	static std::vector<std::string> SeperateStringByChar(std::string str, char c, bool removeZeroLength = true);

	static float StringToFloat(std::string str);

	static int StringToInt(std::string str);
};