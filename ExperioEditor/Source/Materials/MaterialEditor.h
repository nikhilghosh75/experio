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

public:
	MaterialEditor();

	virtual void Display() override;

	void SetMaterial(const std::string& str);
	void SetMaterial(Material* material, uint32_t materialType);

private:
	void DisplayUniform(ShaderParamInfo paramInfo);
};