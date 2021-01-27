#include "MaterialSaver.h"
#include "../Framework/EditorProject.h"
#include "../Framework/SaveParams.h"
#include "Runtime/Debug/Debug.h"

void MaterialSaver::SaveMaterial(Material * material, uint32_t materialType, std::string & filepath)
{
	FShaderInfo& shaderInfo = EditorProject::shaders[materialType - 1];

	std::ofstream outFile(filepath);
	outFile << "MATERIAL" << std::endl;
	outFile << "Type: " << shaderInfo.type << std::endl;
	outFile << std::endl;

	for (size_t i = 0; i < shaderInfo.uniforms.size(); i++)
	{
		SaveUniform(material, shaderInfo.uniforms[i], outFile);
	}
}

void MaterialSaver::SaveUniform(Material * material, ShaderParamInfo & paramInfo, std::ofstream& outFile)
{
	outFile << paramInfo.name << ": ";
	switch (paramInfo.type)
	{
	case EShaderParamType::BOOL: SaveBool(*(bool*)((char*)material + paramInfo.offset), outFile); break;
	case EShaderParamType::FLOAT: SaveFloat(*(float*)((char*)material + paramInfo.offset), outFile); break;
	case EShaderParamType::FLOAT2: SaveVector2(*(FVector2*)((char*)material + paramInfo.offset), outFile); break;
	case EShaderParamType::FLOAT3: SaveVector3(*(FVector3*)((char*)material + paramInfo.offset), outFile); break;
	case EShaderParamType::FLOAT4: SaveVector4(*(FVector4*)((char*)material + paramInfo.offset), outFile); break;
	case EShaderParamType::INT: SaveInt(*(int*)((char*)material + paramInfo.offset), outFile); break;
	case EShaderParamType::TEXTURE: SaveTexture(*(TextureRef*)((char*)material + paramInfo.offset), outFile); break;
	default: Debug::LogError("Uniform Saving Function does not exist"); break;
	}
	outFile << std::endl;
}
