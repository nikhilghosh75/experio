#pragma once

#include "Material.h"
#include "../../Debug/Debug.h"
#include "../../Files/LFileOperations.h"
#include "../../Framework/AssetMap.h"
#include <string>
#include <vector>
#include <fstream>

class MaterialManager
{
protected:
	uint64_t currentIndex = 0;

public:
	std::vector<uint32_t> materialTypes;

	Material* LoadMaterialFromFile(const std::string& filePath)
	{
		if (!LFileOperations::DoesFileHaveExtension(filePath, "material"))
		{
			Debug::LogError("Loaded Material is not a .material file");
			return nullptr;
		}

		return LoadMaterialFromTextFile(filePath);
	}

	Material* LoadMaterialFromTextFile(const std::string& filePath)
	{
		std::ifstream materialFile(filePath);
		if (materialFile.fail())
		{
			Debug::LogError("File " + filePath + " could not be opened");
			return nullptr;
		}

		char word[256];
		materialFile.getline(word, 256);

		std::string materialType;
		std::string shader;
		std::vector<std::string> params;

		materialFile >> word;
		materialFile >> materialType;

		materialFile >> word;
		materialFile.getline(word, 256);
		shader = std::string(word);

		while (materialFile >> word)
		{
			materialFile.getline(word, 256);
			params.push_back(std::string(word));
		}

		return AddMaterial(GetMaterialType(materialType), shader, params);
	}

	void LoadMaterialsFromCollection(const std::string& filePath)
	{
		std::ifstream materialFile(filePath);
		if (materialFile.fail())
		{
			Debug::LogError("File " + filePath + " could not be opened");
			return;
		}
		
		char checksum[9];
		materialFile.read(checksum, 8);
		checksum[8] = 0;
		if (strcmp(checksum, "PBMATCOL") != 0)
		{
			Debug::LogError("File is incorrectly formatted");
			return;
		}

		char header[16];
		materialFile.read(header, 16);
		uint32_t numMaterials = *(uint32_t*)&(header[0]);

		char word[1024];
		char metadata[16];
		for (uint32_t i = 0; i < numMaterials; i++)
		{
			materialFile.read(metadata, 16);
			uint32_t materialType = *(uint32_t*)&(metadata[0]);
			uint32_t materialSize = *(uint32_t*)&(metadata[4]);
			uint32_t materialShaderID = *(uint32_t*)&(metadata[8]);
			std::string materialShader = AssetMap::assetMap.Get(materialShaderID);

			materialFile.read(word, materialSize);
			AddMaterial(materialType, materialShader, metadata);
		}
	}

	uint32_t GetLastMaterialType() { return materialTypes[materialTypes.size() - 1]; }

	virtual uint32_t GetMaterialType(const std::string& materialType) = 0;

	virtual Material* AddMaterial(uint32_t materialType, std::string shader, std::vector<std::string> params) = 0;

	virtual Material* AddMaterial(uint32_t materialType, std::string shader, char* data) = 0;

	virtual void PopMaterial(uint32_t materialType) = 0;

	virtual uint32_t MaterialCount() const = 0;;
};

#define COMPARE_MATERIAL_TYPE(_materialName_, _materialIndex_) if(materialType == _materialName_) return _materialIndex_