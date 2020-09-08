#include "LString.h"
#include "../Math/LMath.h"

std::vector<std::string> LString::SeperateStringByChar(std::string str, char c, bool removeZeroLength)
{
	std::vector<std::string> seperatedStrings;
	int lastChar = -1;
	for (int i = 0; i < str.size(); i++)
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
	for (int i = 0; i < seperatedStrings.size(); i++)
	{
		if (seperatedStrings[i].size() > 0)
		{
			realSeperatedStrings.push_back(seperatedStrings[i]);
		}
	}
	return realSeperatedStrings;
}

float LString::StringToFloat(std::string str)
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

int LString::StringToInt(std::string str)
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

unsigned int LString::HexStringToInt(std::string s)
{
	unsigned int returnValue = 0;
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

constexpr int LString::CharToInt(char c)
{
	return c - 48;
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
