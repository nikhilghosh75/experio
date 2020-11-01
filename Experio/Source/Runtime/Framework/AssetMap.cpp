#include "AssetMap.h"
#include <fstream>

THashtable<unsigned int, std::string> AssetMap::assetMap;

void AssetMap::ReadAssetMap(std::string filepath)
{
	// Add checks here
	std::ifstream inFile(filepath);
	
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
