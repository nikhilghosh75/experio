#pragma once
#include <stdint.h>
#include <string>
#include <fstream>

class GameObject;
class SceneSettings;

class SceneSaver
{
	static void SaveGameObject(GameObject* gameObject, std::ofstream& stream);

	static void SaveSceneSettings(SceneSettings& settings, std::ofstream& stream);
public:
	static bool SaveScene(uint8_t sceneIndex, const std::string& filename);
};