#include "AssetMapSaver.h"
#include "../Core/EditorApplication.h"
#include "../Framework/AssetManager.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Framework/GUID.h"
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
	return currentMap.size();
}

void AssetMapSaver::Insert(const std::string & filepath)
{
	for (size_t i = 0; i < currentMap.size(); i++)
	{
		if (currentMap[i].second == filepath)
		{
			return;
		}
	}
	currentMap.emplace_back(currentMap.size(), filepath);
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
	outFile << "Default Scene: " << LFileOperations::StripFilename(EditorApplication::defaultScenePath) << std::endl;

	for (uint32_t i = 0; i < currentMap.size(); i++)
	{
		Experio::GUID assetGuid = AssetManager::FilenameToGUID(currentMap[i].second);
		outFile << currentMap[i].first << " " << currentMap[i].second << " "
			<< assetGuid.ToString() << std::endl;
	}
}
