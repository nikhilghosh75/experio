#pragma once
#include "../Containers/THashtable.h"
#include <string>

/// <summary>
/// A static class representing an AssetMap, a map between asset IDs and filepaths
/// </summary>

class AssetMap
{
public:
	static THashtable<unsigned int, std::string> assetMap;
	static std::string defaultScenePath;

	static void ReadAssetMap(std::string filepath);

	static void Clear();

	static uint32_t SerializedSizeOfAssetMap();
};