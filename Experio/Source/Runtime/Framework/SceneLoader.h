#pragma once
#include <string>
#include <fstream>
#include "GameObject.h"

enum class ESceneProjectCompareType
{
	None,
	Warning,
	Return
};

class SceneLoader
{
public:
	static void LoadSceneFromFile(std::string filePath, int sceneSlot = 0, ESceneProjectCompareType compareType=ESceneProjectCompareType::None);

private:
	// Helpers
	static bool ShouldQuitOnProjectName(std::string sceneProjectName, ESceneProjectCompareType compareType);

	static void AddComponentsToObjects(std::ifstream& stream, int sceneSlot, GameObject* gameObject);
};