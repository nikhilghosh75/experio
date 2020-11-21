#pragma once
#include <string>

class SceneConverter
{
public:
	static void ConvertSceneToBinary(const std::string& fromFilepath, const std::string& toFilepath);
};