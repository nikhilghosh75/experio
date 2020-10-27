#pragma once
#include <stdint.h>
#include <string>

class SceneSaver
{
public:
	static bool SaveScene(uint8_t sceneIndex, const std::string& filename);
};