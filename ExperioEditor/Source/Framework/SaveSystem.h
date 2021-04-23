#pragma once
#include <string>
#include <vector>

enum class ESaveableAssetType
{
	None,
	Scene,
	Material,
	Value
};

struct FSaveableAsset
{
	ESaveableAssetType type;
	std::string filepath;

	FSaveableAsset();
	FSaveableAsset(ESaveableAssetType type);
	FSaveableAsset(ESaveableAssetType type, std::string filepath);
};

class SaveSystem
{
	static std::vector<FSaveableAsset> currentlyOpenAssets;

public:
	static void SaveAll();

	static void SaveScene();
	static void SaveMaterial();
	static void SaveValues();

	static std::vector<FSaveableAsset> GetCurrentlyOpenAssets();

	static void OpenSaveSelectedScreen();

	static void DisplaySaveSelectedScreen();
};