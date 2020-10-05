#pragma once

#include <string>
#include <vector>

#include "../Math/LMath.h"

class LString
{
public:
	constexpr static int CharToInt(char c);

	static char DigitToChar(int i);

	static std::string GetFileLocation(const std::string fileName);

	static std::string GetFileName(const std::string fileName);

	static std::string FloatToString(float f, int sigFigs = 5);

	static unsigned int HexStringToInt(std::string s);
	static unsigned long long HexStringToLong(std::string s);

	static unsigned int HexCharToInt(char c);

	constexpr static bool IsAlpha(char c);
	constexpr static bool IsAlphaNumeric(char c);
	constexpr static bool IsLower(char c);
	constexpr static bool IsNumeric(char c);
	constexpr static bool IsUpper(char c);

	static std::string LongLongToHexString(uint64_t n);

	template<typename Number>
	static std::string NumberWithCommas(Number n);

	static std::string ReplaceAll(std::string s, char from, char to);

	static std::vector<std::string> SeperateStringByChar(std::string str, char c, bool removeZeroLength = true);

	static float StringToFloat(std::string str);

	static int StringToInt(std::string str);
};

template<typename Number>
std::string LString::NumberWithCommas(Number n)
{
	std::string result = "";
	if (n < 0)
	{
		result += "-";
	}
	if (LMath::Abs((float)n) < 1000)
	{
		result += std::to_string(n);
		return result;
	}

	n = LMath::Abs(n);
	std::string numberString = std::to_string(n);
	for (int i = numberString.size() - 1; i >= 0; i--)
	{
		if (i % 3 == 2 && i != numberString.size() - 1)
		{
			result += ',';
		}
		result += numberString[i];
	}
	return result;
}