#pragma once
#include "../Containers/THashtable.h"
#include <string>

class AssetMap
{
public:
	static THashtable<unsigned int, std::string> assetMap;

	static void ReadAssetMap(std::string filepath);

	static uint32_t SerializedSizeOfAssetMap();
};