#pragma once

#include "MeshMaterial.h"
#include "BillboardMaterial.h"
#include "MaterialManager.h"
#include "../../Debug/Debug.h"
#include "../../Framework/Params.h"

class TestMaterialManager : public MaterialManager
{
	std::vector<MeshMaterial> meshMaterials;

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

		Debug::LogError("MATERIAL TYPE COULD NOT BE FOUND");
		return nullptr;
	}
};