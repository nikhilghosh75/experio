#pragma once
#include <vector>
#include <string>
#include "Runtime\Containers\TPair.h"

class AssetMapSaver
{
	static std::vector<TPair<uint32_t, std::string>> currentMap;
public:
	static void Reset();

	static uint32_t NextAssetMapIndex();

	static uint32_t GetNumAssets();

	static uint32_t GetIndexOfAsset(const std::string& filepath);

	static void PushBack(std::string asset);

	static std::vector<TPair<uint32_t, std::string>>& GetCurrentMap();

	static void SaveToAssetMap(const std::string& filepath);
};