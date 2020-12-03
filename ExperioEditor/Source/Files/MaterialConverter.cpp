#include "MaterialConverter.h"
#include "Runtime/Framework/Project.h"

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

	uint32_t materialType = Project::materialManager->materialTypes[material->GetID()];
	size_t materialSize = SerializedSizeOfMaterial(materialType);
	outFile.write((char*)materialType, 4);
	outFile.write((char*)materialSize, 4);
	outFile.write("ABCDEFGH", 8);

	BinarySaveMaterialToStream(material, materialType, outFile);

	Project::materialManager->PopMaterial(materialType);
}
