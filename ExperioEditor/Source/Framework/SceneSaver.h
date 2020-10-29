#pragma once
#include <stdint.h>
#include <string>
#include <fstream>

class GameObject;

class SceneSaver
{
	static void SaveGameObject(GameObject* gameObject, std::ofstream& stream);
public:
	static bool SaveScene(uint8_t sceneIndex, const std::string& filename);
};