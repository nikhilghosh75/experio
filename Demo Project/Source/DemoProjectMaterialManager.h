#pragma once

#include "Runtime/Rendering/Materials/MaterialManager.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Framework/Params.h"

#include "Runtime/Rendering/Materials/MeshMaterial.h"
#include "Runtime/Rendering/Materials/BillboardMaterial.h"
#include "Runtime/Rendering/Materials/TextMaterial.h"

__declspec(dllexport) class DemoProjectMaterialManager : public MaterialManager
{
	std::vector<MeshMaterial> meshMaterials;
	std::vector<BillboardMaterial> billboardMaterials;
	std::vector<TextMaterial> textMaterials;

public:
	DemoProjectMaterialManager()
	{
		meshMaterials.reserve(96);
		billboardMaterials.reserve(32);
		textMaterials.reserve(8);

		materialTypes.reserve(256);
		currentIndex = 0;
	}

	virtual uint32_t GetMaterialType(const std::string& materialType) override
	{
		COMPARE_MATERIAL_TYPE("MeshMaterial", 1);
		COMPARE_MATERIAL_TYPE("BillboardMaterial", 2);
		COMPARE_MATERIAL_TYPE("SingleColorMaterial", 3);
		return 0;
	}

	virtual Material* AddMaterial(uint32_t materialType, std::string shader, std::vector<std::string> params) override
	{
		Shader* matShader = ParseShader(shader);
		this->currentIndex++;
		this->materialTypes.push_back(materialType);

		switch (materialType)
		{
		case 1:
		{
			MeshMaterial& newMaterial = meshMaterials.emplace_back(matShader, currentIndex);
			newMaterial.albedo = ParseTexture(params[0]);
			newMaterial.normal = ParseTexture(params[1]);
			newMaterial.specular = ParseTexture(params[2]);
			return &newMaterial;
		}
		case 2:
		{
			BillboardMaterial newMaterial = billboardMaterials.emplace_back(matShader, currentIndex);
			return &newMaterial;
		}
		}

		Debug::LogError("MATERIAL TYPE COULD NOT BE FOUND");
		return nullptr;
	}

	virtual void PopMaterial(uint32_t materialType) override
	{
		switch (materialType)
		{
		case 1: meshMaterials.pop_back(); return;
		case 2: billboardMaterials.pop_back(); return;
		}
	}

	virtual uint32_t MaterialCount() const override
	{
		return meshMaterials.size() + billboardMaterials.size();
	}
};