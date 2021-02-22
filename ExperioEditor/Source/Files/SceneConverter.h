#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Runtime/Math/FQuaternion.h"
#include "Runtime/Math/FVector3.h"

class FileBuffer;

class SceneConverter
{
public:
	static void LegacyConvertSceneToBinary(const std::string& fromFilepath, const std::string& toFilepath);

	static void ConvertSceneToBinary(const std::string& fromFilepath, const std::string& toFilepath);

	static size_t SerializedSizeOfScene(const std::string& filepath);

private:
	class GameObjectInfo
	{
	public:
		uint8_t layer;
		uint16_t tag;
		std::string name;
		uint32_t parentIndex;
		uint8_t numChildren;
		bool isActive;
		FVector3 position;
		FQuaternion rotation;
		FVector3 scale;
		uint32_t tempID;
	};

	//  ---- Header ----
	static void GenerateHeader(const FileBuffer& buffer, std::ofstream& outFile);

	static uint32_t GetNumGameObjects(const FileBuffer& buffer);

	static uint32_t GetNumComponents(const FileBuffer& buffer);

	static std::string GetName(const FileBuffer& buffer);

	//  ---- Game Objects ----
	static void GenerateGameObject(const FileBuffer& buffer, std::ofstream& outFile);

	static std::vector<GameObjectInfo> GenerateGameObjectInfos(const FileBuffer& buffer);

	static void ParseGameObject(const FileBuffer& buffer, std::vector<GameObjectInfo>& gameObjects, size_t parentIndex, size_t start, size_t end);

	static void SaveGameObject(const GameObjectInfo& info, std::ofstream& outFile);

	static size_t FindEndBrace(const FileBuffer& buffer, size_t start);

	//  ---- Components ----
	static void GenerateComponent(const FileBuffer& buffer, std::ofstream& outFile);

	static void ParseComponents(const FileBuffer& buffer, std::ofstream& outFile, uint32_t gameObject, size_t start, size_t end);

	static size_t FindEndCurlyBrace(const FileBuffer& buffer, size_t start);
};