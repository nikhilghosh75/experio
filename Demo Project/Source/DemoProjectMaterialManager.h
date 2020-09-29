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

	virtual Material* AddMaterial(std::string materialType, std::string shader, std::vector<std::string> params)
	{
		Shader* matShader = ParseShader(shader);
		if (materialType.find("MeshMaterial") != std::string::npos)
		{
			MeshMaterial* newMaterial = new MeshMaterial(matShader);
			newMaterial->albedo = ParseTexture(params[0]);
			newMaterial->normal = ParseTexture(params[1]);
			newMaterial->specular = ParseTexture(params[2]);
			meshMaterials.push_back(*newMaterial);
			return newMaterial;
		}
		if (materialType.find("BillboardMaterial") != std::string::npos)
		{
			BillboardMaterial* newMaterial = new BillboardMaterial(matShader);
			billboardMaterials.push_back(*newMaterial);
			return newMaterial;
		}

		Debug::LogError("MATERIAL TYPE COULD NOT BE FOUND");
		return nullptr;
	}
};