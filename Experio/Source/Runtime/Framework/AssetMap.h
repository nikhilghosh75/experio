#pragma once
#include "../Containers/THashtable.h"
#include <string>

class AssetMap
{
public:
	static THashtable<unsigned int, std::string> assetMap;
	static std::string defaultScenePath;

	static void ReadAssetMap(std::string filepath);

	static void Clear();

	static uint32_t SerializedSizeOfAssetMap();
};