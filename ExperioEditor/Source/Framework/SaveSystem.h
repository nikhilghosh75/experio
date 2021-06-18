#pragma once
#include <string>
#include <vector>
#include "imgui.h"
#include "NotificationSystem.h"

enum class ESaveableAssetType
{
	None,
	Scene,
	Material,
	Value,
	Flowchart
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
	static std::vector<bool> shouldSaveAssets;

	static float timeSinceAutosave;
	static TextNotification* autosaveNotification;

	static ImVec4 AssetTypeToColor(ESaveableAssetType assetType);

	static char* AssetTypeToString(ESaveableAssetType assetType);

	static void SaveAssetOfType(ESaveableAssetType assetType);

	static void Autosave();

public:
	static void Initialize();

	static void Update();

	// ---- Saving -----
	static void SaveAll();

	static void SaveScene();
	static void SaveMaterial();
	static void SaveValues();
	static void SaveFlowcharts();

	// ---- Locking -----
	static void LockAll();

	static void LockScene();
	static void LockMaterial();
	static void LockValues();
	static void LockFlowcharts();

	static void UnlockAll();

	static void UnlockScene();
	static void UnlockMaterial();
	static void UnlockValues();
	static void UnlockFlowcharts();

	static std::vector<FSaveableAsset> GetCurrentlyOpenAssets();

	static void OpenSaveSelectedScreen();

	static void DisplaySaveSelectedScreen();
};