#include "BuildSystem/BinarySaveParams.h"
#include "Framework/SaveParams.h"

#include "Runtime/Rendering/Materials/MeshMaterial.h"
#include "Runtime/Rendering/Materials/BillboardMaterial.h"
#include "Runtime/Rendering/Materials/TextMaterial.h"

template<class T> void SaveMaterial(T* material, std::ostream& stream) {};

void SaveMaterialToStream(Material* material, uint32_t materialIndex, std::ofstream& stream)
{
	switch (materialIndex)
	{
	case 1: SaveMaterial((MeshMaterial*)material, stream); return;
	case 2: SaveMaterial((BillboardMaterial*)material, stream); return;
	}
}

void SaveMaterial<MeshMaterial>(MeshMaterial* material, std::ostream& stream)
{
	SaveTexture(material->albedo, stream);
	SaveTexture(material->normal, stream);
	SaveTexture(material->specular, stream);
}

template<class T> void BinarySaveMaterial(T* material, std::ostream& stream) {};

void BinarySaveMaterialToStream(Material* material, uint32_t materialType, std::ofstream& stream)
{
	switch (materialType)
	{
	case 1: BinarySaveMaterial((MeshMaterial*)material, stream); return;
	case 2: BinarySaveMaterial((BillboardMaterial*)material, stream); return;
	}
}

void BinarySaveMaterial<MeshMaterial>(MeshMaterial* material, std::ostream& stream)
{
	BinarySaveTexture(material->albedo, stream);
	BinarySaveTexture(material->normal, stream);
	BinarySaveTexture(material->specular, stream);
}

uint32_t SerializedSizeOfMaterial(uint32_t materialType)
{
	switch (materialType)
	{
	case 1: return 12;
	case 2: return 0;
	}
	return 0;
}