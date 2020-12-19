#include "AssetMap.h"
#include <fstream>
#include "../Debug/Debug.h"
#include "../Files/LFileOperations.h"

THashtable<unsigned int, std::string> AssetMap::assetMap;

void AssetMap::ReadAssetMap(std::string filepath)
{
	if (!LFileOperations::DoesFileHaveExtension(filepath, "pbasm"))
	{
		Debug::LogError("Filepath is not a pbasm file");
		return;
	}

	std::ifstream inFile(filepath);
	if (inFile.bad())
	{
		Debug::LogError("Asset Map cannot be opened");
		return;
	}
	
	char word[256];
	inFile.getline(word, 256);

	unsigned int numAssets;
	inFile >> numAssets;

	for (int i = 0; i < numAssets; i++)
	{
		unsigned int assetIndex;
		std::string assetFilepath;

		inFile >> assetIndex >> assetFilepath;
		assetMap.Insert(assetIndex, assetFilepath);
	}
}

uint32_t AssetMap::SerializedSizeOfAssetMap()
{
	return assetMap.GetSize() * 4;
}
