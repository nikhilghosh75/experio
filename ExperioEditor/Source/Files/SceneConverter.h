#pragma once
#include <string>
#include <fstream>

class FileBuffer;

class SceneConverter
{
public:
	static void ConvertSceneToBinary(const std::string& fromFilepath, const std::string& toFilepath);

	static void ExperimentalConvertSceneToBinary(const std::string& fromFilepath, const std::string& toFilepath);

private:
	static void GenerateHeader(const FileBuffer& buffer, std::ofstream& outFile);

	static uint32_t GetNumGameObjects(const FileBuffer& buffer);

	static uint32_t GetNumComponents(const FileBuffer& buffer);

	static std::string GetName(const FileBuffer& buffer);

	static void GenerateGameObject(const FileBuffer& buffer, std::ofstream& outFile);
};