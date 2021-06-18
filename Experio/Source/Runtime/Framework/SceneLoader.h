#pragma once
#include <string>
#include <fstream>
#include "GameObject.h"

class SceneSettings;

enum class ESceneProjectCompareType
{
	None,
	Warning,
	Return
};

/// <summary>
/// A class abstracting the loading of a scene
/// Includes binary and text loading
/// </summary>

class SceneLoader
{
	friend class SceneConverter;

public:
	static bool LoadSceneFromFile(std::string filePath, int sceneSlot = 0, ESceneProjectCompareType compareType=ESceneProjectCompareType::None);

private:
	static bool LoadSceneFromTextFile(std::string filePath, int sceneSlot, ESceneProjectCompareType compareType);
	static bool LoadSceneFromBinaryFile(std::string filePath, int sceneSlot = 0);

	// Text Helpers
	static bool ShouldQuitOnProjectName(std::string sceneProjectName, ESceneProjectCompareType compareType);

	static void ParseSettingsText(std::istream& stream, SceneSettings& settings);

	static void AddComponentsToObjects(std::ifstream& stream, int sceneSlot, GameObject* gameObject);

	// Binary Helpers
	static void LoadSceneData(uint32_t dataIndex);

	static void ParseSettingsBinary(std::ifstream& stream, SceneSettings& settings, unsigned int size);
};