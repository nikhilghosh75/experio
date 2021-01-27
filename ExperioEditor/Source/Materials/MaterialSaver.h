#pragma once
#include "Runtime/Rendering/Materials/Material.h"
#include "../Framework/ShaderInfo.h"
#include <fstream>

class MaterialSaver
{
public:
	static void SaveMaterial(Material* material, uint32_t materialType, std::string& filepath);

private:
	static void SaveUniform(Material * material, ShaderParamInfo& paramInfo, std::ofstream& outFile);
};