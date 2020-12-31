#include "MaterialConverter.h"
#include "Runtime/Framework/Project.h"
#include <iostream>

std::ofstream MaterialConverter::outFile;

extern void BinarySaveMaterialToStream(Material* material, uint32_t materialType, std::ofstream& stream);

extern uint32_t SerializedSizeOfMaterial(uint32_t materialType);

void MaterialConverter::StartMaterialCollection(const std::string & filepath, uint32_t numMaterials)
{
	outFile.close();
	outFile.open(filepath, std::ios::out | std::ios::binary);

	uint32_t localNumMaterials = numMaterials;
	outFile.write("PBMATCOL", 8);
	outFile.write((char*)&localNumMaterials, 4);
	outFile.write("ABCDEFGHIJKL", 12);
}

void MaterialConverter::EndMaterialCollection()
{
	outFile.close();
}

void MaterialConverter::MaterialToBinaryMaterial(const std::string & fromFilepath)
{
	Material* material = Project::materialManager->LoadMaterialFromFile(fromFilepath);

	uint64_t materialId = material->GetID();
	std::cout << materialId << " " << Project::materialManager->materialTypes.size() << std::endl;
	uint32_t materialType = Project::materialManager->materialTypes[materialId];
	size_t materialSize = SerializedSizeOfMaterial(materialType);

	outFile.write((char*)&materialType, 4);
	outFile.write((char*)&materialSize, 4);
	outFile.write("ABCDEFGH", 8);

	BinarySaveMaterialToStream(material, materialType, outFile);

	Project::materialManager->PopMaterial(materialType);
}
