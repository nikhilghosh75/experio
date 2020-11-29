#pragma once

#include "Material.h"
#include "../../Files/LFileOperations.h"
#include "../../Debug/Debug.h"
#include <string>
#include <vector>
#include <fstream>

class MaterialManager
{
protected:
	uint64_t currentIndex = 0;

public:
	std::vector<uint32_t> materialTypes;

	Material* LoadMaterialFromFile(std::string filePath)
	{
		if (!LFileOperations::DoesFileHaveExtension(filePath, "material"))
		{
			Debug::LogError("Loaded Material is not a .material file");
			return nullptr;
		}

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

	virtual uint32_t GetMaterialType(const std::string& materialType) = 0;

	virtual Material* AddMaterial(uint32_t materialType, std::string shader, std::vector<std::string> params) = 0;

	virtual void PopMaterial(uint32_t materialType) = 0;

	virtual uint32_t MaterialCount() const = 0;;
};

#define COMPARE_MATERIAL_TYPE(_materialName_, _materialIndex_) if(materialType == _materialName_) return _materialIndex_