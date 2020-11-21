#include "AssetMapSaver.h"
#include <fstream>

std::vector<TPair<uint32_t, std::string>> AssetMapSaver::currentMap;

void AssetMapSaver::Reset()
{
	currentMap.clear();
}

uint32_t AssetMapSaver::NextAssetMapIndex()
{
	return currentMap.size();
}

uint32_t AssetMapSaver::GetNumAssets()
{
	return currentMap.size();
}

uint32_t AssetMapSaver::GetIndexOfAsset(const std::string & filepath)
{
	for (size_t i = 0; i < currentMap.size(); i++)
	{
		if (currentMap[i].second == filepath)
		{
			return currentMap[i].first;
		}
	}
	return 0;
}

void AssetMapSaver::PushBack(std::string asset)
{
	currentMap.emplace_back((uint32_t)currentMap.size(), asset);
}

std::vector<TPair<uint32_t, std::string>>& AssetMapSaver::GetCurrentMap()
{
	return currentMap;
}

void AssetMapSaver::SaveToAssetMap(const std::string & filepath)
{
	std::ofstream outFile(filepath);

	outFile << "EXPERIO ASSET MAP" << std::endl;
	outFile << currentMap.size() << std::endl;

	for (uint32_t i = 0; i < currentMap.size(); i++)
	{
		outFile << currentMap[i].first << " " << currentMap[i].second << std::endl;
	}
}
