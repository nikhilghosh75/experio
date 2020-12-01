#pragma once
#include <string>
#include <fstream>

class MaterialConverter
{
	static std::ofstream outFile;
public:
	static void StartMaterialCollection(const std::string& filepath, uint32_t numMaterials);

	static void EndMaterialCollection();

	static void MaterialToBinaryMaterial(const std::string& fromFilepath);
};