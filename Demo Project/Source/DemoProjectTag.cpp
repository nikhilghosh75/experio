#include <cstring>
#include <string>

#ifndef EXPERIO_EDITOR

unsigned short DefaultTagStringToNum(const char* string)
{
	if (strcmp(string, "Player"))
	{
		return 1;
	}
	if (strcmp(string, "Enemy"))
	{
		return 2;
	}
	return 0;
}

std::string DefaultTagNumToString(unsigned short num)
{
	switch (num)
	{
	case 1:
		return "Player";
	case 2:
		return "Enemy";
	}
	return "";
}

#endif