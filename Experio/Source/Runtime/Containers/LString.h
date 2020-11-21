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

	static std::vector<size_t> FindAllOfChar(const std::string& str, char c);

	static size_t FindFirstOfChars(const std::string& str, std::vector<char> chars);
	static size_t FindFirstOfChars(const std::string& str, std::vector<char> chars, size_t firstIndex);

	static std::string FloatToString(float f, int sigFigs = 5);

	static bool HasAlpha(const std::string& str);
	static bool HasAlphaNumeric(const std::string& str);
	static bool HasChar(const std::string& str, char c);
	static bool HasChars(const std::string& str, const std::vector<char>& chars);
	static bool HasOneOfEachChar(const std::string& str, const std::vector<char>& chars);
	static bool HasNumeric(const std::string& str);

	static unsigned int HexCharToInt(char c);

	static unsigned int HexStringToInt(const std::string& s);
	static unsigned long long HexStringToLong(const std::string& s);

	constexpr static bool IsAlpha(char c);
	constexpr static bool IsAlphaNumeric(char c);
	constexpr static bool IsLower(char c);
	constexpr static bool IsNumeric(char c);
	constexpr static bool IsUpper(char c);
	static bool IsWhitespace(char c);

	static std::string LongLongToHexString(uint64_t n);

	template<typename Number>
	static std::string NumberWithCommas(Number n);

	static size_t NumOfChars(const std::string& s, char c);

	static std::string ReplaceAll(std::string s, char from, char to);

	static std::vector<std::string> SeperateStringByChar(std::string str, char c, bool removeZeroLength = true);

	static float StringToFloat(const std::string& str);

	static int StringToInt(const std::string& str);

	static unsigned int StringToUInt(const std::string& str);

	static std::string Trim(std::string str);
	static std::string TrimLeft(std::string str);
	static std::string TrimRight(std::string str);
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

	n = LMath::Abs((float)n);
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