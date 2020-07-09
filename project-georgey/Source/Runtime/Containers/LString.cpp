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
