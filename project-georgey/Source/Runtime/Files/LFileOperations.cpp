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
