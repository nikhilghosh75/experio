#pragma once
#include "../Core/EditorModule.h"
#include "../Framework/ShaderInfo.h"
#include <string>
#include "Runtime/Rendering/Materials/Material.h"

class MaterialEditor : public EditorModule
{
	Material* material;
	uint32_t materialType;
	FShaderInfo shaderInfo;
	std::string materialName;
	std::string filepath;

public:
	static MaterialEditor* materialEditor;

	MaterialEditor();

	virtual void Display() override;

	void SaveMaterial();

	void SetMaterial(const std::string& filepath);
	void SetMaterial(Material* material, uint32_t materialType);

private:
	void DisplayUniform(ShaderParamInfo paramInfo);
};