#include "LString.h"
#include <sstream>
#include <algorithm>

size_t LString::NumOfChars(const std::string & s, char c)
{
	size_t amount = 0;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == c) amount++;
	}
	return amount;
}

size_t LString::NumOfCharsFront(const std::string & s, char c)
{
	size_t amount = 0;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == c)
			amount++;
		else
			return amount;
	}
	return amount;
}

size_t LString::NumWords(const std::string& s)
{
	size_t numWords = 1;
	for (size_t i = 1; i < s.size(); i++)
	{
		if (s[i - 1] == ' ' && s[i] != ' ')
		{
			numWords++;
		}
	}

	if (s[0] == ' ')
	{
		numWords--;
	}
	return numWords;
}

std::string LString::ReplaceAll(std::string s, char from, char to)
{
	std::string returnString = s;
	size_t foundPosition = returnString.find_first_of(from);
	while (foundPosition != std::string::npos)
	{
		returnString = returnString.replace(foundPosition, 1, 1, to);
		foundPosition = returnString.find_first_of(from);
	}
	return returnString;
}

std::vector<std::string> LString::SeperateStringByChar(const std::string& str, char c, bool removeZeroLength)
{
	std::vector<std::string> seperatedStrings;
	int lastChar = -1;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == c)
		{
			seperatedStrings.push_back(str.substr(lastChar + 1, i - lastChar - 1));
			lastChar = i;
		}
	}

	seperatedStrings.push_back(str.substr(lastChar + 1, str.size() - lastChar - 1));

	if (!removeZeroLength)
	{
		return seperatedStrings;
	}

	std::vector<std::string> realSeperatedStrings;
	for (size_t i = 0; i < seperatedStrings.size(); i++)
	{
		if (seperatedStrings[i].size() > 0)
		{
			realSeperatedStrings.push_back(seperatedStrings[i]);
		}
	}
	return realSeperatedStrings;
}


float LString::SubstrToFloat(const std::string& str, size_t start, size_t end)
{
	float integer = 0.f, fraction = 0.f;
	uint8_t denominator = 0;
	bool beforeDecimal = true, isPositive = true;
	for (size_t i = start; i < end; i++)
	{
		if (str[i] == '-')
		{
			isPositive = false;
		}
		else if (str[i] == '.')
		{
			beforeDecimal = false;
		}
		else if (IsNumeric(str[i]))
		{
			if (beforeDecimal)
			{
				integer = (integer * 10) + CharToInt(str[i]);
			}
			else
			{
				fraction = (fraction * 10) + CharToInt(str[i]);
				denominator++;
			}
		}
	}
	return isPositive ? integer + (fraction / (float)LMath::PowOfTen(denominator)) : (integer + (fraction / (float)LMath::PowOfTen(denominator))) * -1.f;
}

bool LString::StringToBool(const std::string& str)
{
	if (str[0] == 't' || str[0] == 'T')
		return true;
	return false;

}

float LString::StringToFloat(const std::string& str)
{
	float integer = 0.f, fraction = 0.f;
	uint8_t denominator = 0;
	bool beforeDecimal = true, isPositive = true;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '-')
		{
			isPositive = false;
		}
		else if (str[i] == '.')
		{
			beforeDecimal = false;
		}
		else if (IsNumeric(str[i]))
		{
			if (beforeDecimal) 
			{ 
				integer = (integer * 10) + CharToInt(str[i]);
			}
			else
			{
				fraction = (fraction * 10) + CharToInt(str[i]);
				denominator++;
			}
		}
	}
	return isPositive ? integer + (fraction / (float)LMath::PowOfTen(denominator)) : (integer + (fraction / (float)LMath::PowOfTen(denominator))) * -1.f;
}

std::vector<float> LString::StringToFloatVector(const std::string & str, char seperator)
{
	std::vector<float> v;
	v.reserve(LString::NumOfChars(str, seperator));

	float integer = 0.f, fraction = 0.f;
	uint8_t denominator = 0;
	bool beforeDecimal = true, isPositive = true;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == seperator)
		{
			v.push_back(isPositive ? integer + (fraction / (float)LMath::PowOfTen(denominator)) : (integer + (fraction / (float)LMath::PowOfTen(denominator))) * -1.f);
			beforeDecimal = true, isPositive = true;
			denominator = 0;
			integer = 0.f, fraction = 0.f;
		}
		else if (str[i] == '-')
		{
			isPositive = false;
		}
		else if (str[i] == '.')
		{
			beforeDecimal = false;
		}
		else if (IsNumeric(str[i]))
		{
			if (beforeDecimal)
			{
				integer = (integer * 10) + CharToInt(str[i]);
			}
			else
			{
				fraction = (fraction * 10) + CharToInt(str[i]);
				denominator++;
			}
		}
	}
	v.push_back(isPositive ? integer + (fraction / (float)LMath::PowOfTen(denominator)) : (integer + (fraction / (float)LMath::PowOfTen(denominator))) * -1.f);
	return v;
}

int LString::SubstrToInt(const std::string& str, size_t start, size_t end)
{
	int integer = 0;
	bool isPositive = true;
	for (size_t i = start; i < end; i++)
	{
		if (str[i] == '-')
		{
			isPositive = false;
		}
		else if (IsNumeric(str[i]))
		{
			integer = (integer * 10) + CharToInt(str[i]);
		}
	}
	return isPositive ? integer : integer * -1;
}

int LString::StringToInt(const std::string& str)
{
	int integer = 0;
	bool isPositive = true;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '-')
		{
			isPositive = false;
		}
		else if (IsNumeric(str[i]))
		{
			integer = (integer * 10) + CharToInt(str[i]);
		}
	}
	return isPositive ? integer : integer * -1;
}

uint8_t LString::StringToUByte(const std::string& str)
{
	uint8_t unsignedByte = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (IsNumeric(str[i]))
		{
			unsignedByte = (unsignedByte * 10) + CharToInt(str[i]);
		}
	}
	return unsignedByte;
}

unsigned int LString::SubstrToUInt(const std::string& str, size_t start, size_t end)
{
	unsigned int unsignedInteger = 0;
	for (size_t i = start; i < end; i++)
	{
		if (IsNumeric(str[i]))
		{
			unsignedInteger = (unsignedInteger * 10) + CharToInt(str[i]);
		}
	}
	return unsignedInteger;
}

unsigned int LString::StringToUInt(const std::string & str)
{
	unsigned int unsignedInteger = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (IsNumeric(str[i]))
		{
			unsignedInteger = (unsignedInteger * 10) + CharToInt(str[i]);
		}
	}
	return unsignedInteger;
}

std::string LString::ToCamelCase(const std::string& str)
{
	std::string camelCaseStr = str;
	camelCaseStr[0] = ToLower(camelCaseStr[0]);
	return camelCaseStr;
}

char LString::ToLower(char c)
{
	if (c >= 'A' && c <= 'Z') return c + 32;
	return c;
}

char LString::ToUpper(char c)
{
	if (c >= 'a' && c <= 'z') return c - 32;
	return c;
}

std::string LString::Trim(std::string str)
{
	return TrimLeft(TrimRight(str));
}

std::string LString::TrimLeft(std::string str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c) {return !LString::IsWhitespace(c); }));
	return str;
}

std::string LString::TrimRight(std::string str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char c) {return !LString::IsWhitespace(c); }).base(), str.end());
	return str;
}

unsigned int LString::HexStringToInt(const std::string& s)
{
	unsigned int returnValue = 0;
	int n = s.size();
	for (int i = 0; i < n; i++)
	{
		returnValue += LMath::PowOfTwo(n - i - 1) * HexCharToInt(s[i]);
	}

	return returnValue;
}

unsigned long long LString::HexStringToLong(const std::string& s)
{
	unsigned long long returnValue = 0;
	int n = s.size();
	for (int i = 0; i < n; i++)
	{
		returnValue += LMath::PowOfTwo(n - i - 1) * HexCharToInt(s[i]);
	}
	return returnValue;
}

unsigned int LString::HexCharToInt(char c)
{
	if (c > 47 && c < 58)
	{
		return c - 48;
	}
	if (c > 64 && c < 91)
	{
		return c - 65 + 10;
	}
	if (c > 96 && c < 123)
	{
		return c - 97 + 10;
	}
	return 0;
}

constexpr bool LString::IsAlpha(char c)
{
	return (c > 64 && c < 91) || (c > 96 && c < 121);
}

constexpr bool LString::IsAlphaNumeric(char c)
{
	return IsAlpha(c) || IsNumeric(c);
}

constexpr bool LString::IsLower(char c)
{
	return c > 96 && c < 121;
}

constexpr bool LString::IsNumeric(char c)
{
	return c > 47 && c < 58;
}

constexpr bool LString::IsUpper(char c)
{
	return c > 64 && c < 91;
}

bool LString::IsWhitespace(char c)
{
	return c == ' ' || c == '\n' || c == '\t';
}

bool LString::IsOnlyWhitespace(const std::string & str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != '\n' && str[i] != '\t' && str[i] != '\r') return false;
	}
	return true;
}

size_t LString::LevenshteinDistance(const std::string& str1, const std::string& str2)
{
	if (str1.empty())
		return str2.size();
	if (str2.empty())
		return str1.size();

	std::vector<size_t> costs(str2.size() + 1);

	for (size_t i = 0; i < str2.size() + 1; i++)
		costs[i] = i;

	for (size_t i = 0; i < str1.size(); i++)
	{
		costs[0] = i + 1;
		size_t corner = i;
		for (size_t j = 0; j < str2.size(); j++)
		{
			size_t upper = costs[j + 1];
			if (costs[i] == costs[j])
				costs[j + 1] = corner;
			else
			{
				size_t t = upper < corner ? upper : corner;
				costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
			}

			corner = upper;
		}
	}

	return costs.back();
}

std::string LString::LongLongToHexString(uint64_t n)
{
	std::stringstream ss;
	ss << std::hex << n;
	return ss.str();
}

size_t LString::Mismatch(const std::string& str1, const std::string& str2)
{
	size_t size = str1.size() > str2.size() ? str1.size() : str2.size();
	for (size_t i = 0; i < size; i++)
	{
		if (str1[i] != str2[i])
			return i;
	}
	return str1.size() < str2.size() ? str1.size() : str2.size();
}

std::string LString::BoolToString(bool b)
{
	return b ? "true" : "false";
}

constexpr int LString::CharToInt(char c)
{
	return c - 48;
}

bool LString::CompareSubstr(const std::string & original, const std::string & substr, size_t offset)
{
	for (size_t i = 0; i < substr.size(); i++)
	{
		if (substr[i] != original[i + offset])
			return false;
	}
	return true;
}

char LString::DigitToChar(int i)
{
	return (i % 10) + '0';
}

std::string LString::GetFileLocation(const std::string fileName)
{
	size_t lastSlash = fileName.rfind("/");
	return fileName.substr(0, lastSlash);
}

std::string LString::GetFileName(const std::string fileName)
{
	size_t lastSlash = fileName.rfind("/");
	return fileName.substr(lastSlash + 1);
}

std::vector<size_t> LString::FindAllOfChar(const std::string & str, char c)
{
	std::vector<size_t> v;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == c)
			v.push_back(i);
	}
	return v;
}

size_t LString::FindFirstOfChar(const std::string & str, char c)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == c) return i;
	}
	return str.size();
}

size_t LString::FindFirstOfChars(const std::string & str, std::vector<char> chars)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		for (size_t j = 0; j < chars.size(); j++)
		{
			if (str[i] == chars[j]) return i;
		}
	}
	return std::string::npos;
}

size_t LString::FindFirstOfChars(const std::string & str, std::vector<char> chars, size_t firstIndex)
{
	for (size_t i = firstIndex; i < str.size(); i++)
	{
		for (size_t j = 0; j < chars.size(); j++)
		{
			if (str[i] == chars[j]) return i;
		}
	}
	return std::string::npos;
}

std::string LString::FloatToString(float f, int sigFigs)
{
	std::stringstream ss;
	int trunc = (int)f;
	ss << trunc;
	float remainder = f - (float)trunc;
	ss << '.';
	float pow = 1;
	for (int i = 0; i < sigFigs; i++)
	{
		pow *= 10.f;
		remainder = fmod(remainder, 10.f);
		trunc = (int)(remainder * pow);
		ss << trunc;
	}
	return ss.str();
}

bool LString::FuzzyMatch(const std::string& input, const std::string& hint)
{
	int numMatching = 0;
	
	for (size_t i = 0; i < hint.size(); i++)
	{
		if (input[numMatching] == hint[i])
		{
			numMatching++;
			if (numMatching == input.size())
				return true;
		}
	}

	return numMatching > input.size() - 2;
}

bool LString::FuzzyMatch(const char* input, const char* hint)
{
	int numMatching = 0;
	int inputSize = strlen(input);

	while (*hint != '\0')
	{
		if (*input == *hint)
		{
			numMatching++;
			++input;
			if (*input == '\0')
				return true;
		}
		++hint;
	}

	return numMatching > inputSize - 2;
}

size_t LString::HammingDistance(const std::string& str1, const std::string& str2)
{
	size_t distance = 0;
	size_t minLength = str1.size() < str2.size() ? str1.size() : str2.size();
	size_t maxLength = str1.size() > str2.size() ? str1.size() : str2.size();

	for (size_t i = 0; i < minLength; i++)
	{
		if (str1[i] != str2[i])
			distance++;
	}
	return distance + (maxLength - minLength);
}

bool LString::HasAlpha(const std::string & str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (IsAlpha(str[i])) return true;
	}
	return false;
}

bool LString::HasAlphaNumeric(const std::string & str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (IsAlphaNumeric(str[i])) return true;
	}
	return false;
}

bool LString::HasChar(const std::string & str, char c)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == c) return true;
	}
	return false;
}

bool LString::HasChars(const std::string & str, const std::vector<char>& chars)
{
	for (int i = 0; i < str.size(); i++)
	{
		for (int j = 0; j < chars.size(); j++)
		{
			if (str[i] == chars[j]) return true;
		}
	}
	return false;
}

bool LString::HasOneOfEachChar(const std::string & str, const std::vector<char>& chars)
{
	std::vector<bool> foundChars;
	foundChars.reserve(chars.size());

	for (int i = 0; i < chars.size(); i++)
	{
		foundChars.push_back(false);
	}

	for (int i = 0; i < str.size(); i++)
	{
		for (int j = 0; j < chars.size(); j++)
		{
			if (str[i] == chars[j]) foundChars[j] = true; break;
		}

		bool allFound = true;
		for (int j = 0; j < chars.size(); j++)
		{
			if (!foundChars[j]) allFound = false; break;
		}
		
		if (allFound) return true;
	}
	return false;
}

bool LString::HasNumeric(const std::string & str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (IsNumeric(str[i])) return true;
	}
	return false;
}
