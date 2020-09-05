#pragma once

#include "Material.h"
#include "../../Files/LFileOperations.h"
#include "../../Debug/Debug.h"
#include <string>
#include <vector>
#include <fstream>

class MaterialManager
{
public:
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
		materialFile.getline(word, 256);
		materialType = std::string(word);

		materialFile >> word;
		materialFile.getline(word, 256);
		shader = std::string(word);

		while (materialFile >> word)
		{
			materialFile.getline(word, 256);
			params.push_back(std::string(word));
		}

		return AddMaterial(materialType, shader, params);
	}

	virtual Material* AddMaterial(std::string materialType, std::string shader, std::vector<std::string> params) { return nullptr; }
};