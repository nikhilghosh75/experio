#include "LFileOperations.h"

bool LFileOperations::DoesFileHaveExtension(std::string filePath, const char * extension)
{
	int indexOfDot = 0;

	for (int i = filePath.size() - 2; i >= 2; i--)
	{
		if (filePath[i] == '.')
		{
			indexOfDot = i;
			break;
		}
	}

	return strcmp(&filePath[indexOfDot + 1], extension) == 0;
}

std::string LFileOperations::GetExtension(std::string filePath)
{
	int indexOfDot = 0;

	for (int i = filePath.size() - 2; i >= 2; i--)
	{
		if (filePath[i] == '.')
		{
			indexOfDot = i;
			break;
		}
	}

	return filePath.substr(indexOfDot + 1);
}

std::string LFileOperations::GetFullFilePath(std::string filePath)
{
	if (filePath[0] == ' ')
	{
		filePath = filePath.substr(1);
	}

	if (filePath[0] == '?')
	{
		if (filePath.find("?Standard?") != std::string::npos)
		{
			return "C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard" + filePath.substr(10);
		}
	}
	return "C:/Users/debgh/source/repos/project-bloo/" + filePath;
}
