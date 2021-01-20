#pragma once
#include <string>
#include <vector>
#include "Runtime/Rendering/Managers/TextureManager.h"
#include "Runtime/Rendering/Materials/Material.h"

enum class EShaderParamType
{
	BOOL,
	BOOL2,
	BOOL3,
	BOOL4,
	INT,
	INT2,
	INT3,
	INT4,
	FLOAT,
	FLOAT2,
	FLOAT3,
	FLOAT4,
	MAT2,
	MAT3,
	MAT4,
	TEXTURE,
	CUBEMAP
};

struct ShaderParamInfo
{
	EShaderParamType type;
	std::string name;
	size_t offset;

	ShaderParamInfo() = default;

	ShaderParamInfo(EShaderParamType type, std::string name, size_t offset)
	{
		this->type = type;
		this->name = name;
		this->offset = offset;
	}
};

struct FShaderInfo
{
	std::string name;
	bool isCustom;
	std::string type;
	size_t sizeOfShader;

	std::vector<ShaderParamInfo> uniforms;

	FShaderInfo() = default;

	FShaderInfo(std::string name)
	{
		this->name = name;
		this->type = "MeshMaterial";
		this->isCustom = false;
		this->sizeOfShader = sizeof(Material);
	}

	FShaderInfo(std::string name, bool isCustom)
	{
		this->name = name;
		this->isCustom = isCustom;
		this->type = "MeshMaterial";
		this->sizeOfShader = sizeof(Material);
	}

	static size_t SizeOfParam(EShaderParamType paramType)
	{
		switch (paramType)
		{
		case EShaderParamType::BOOL: return 1;
		case EShaderParamType::BOOL2: return 2;
		case EShaderParamType::BOOL3: return 3;
		case EShaderParamType::BOOL4: return 4;
		case EShaderParamType::FLOAT: return 4;
		case EShaderParamType::TEXTURE: return sizeof(TextureRef);
		}
		return 0;
	}

	void PushUniform(ShaderParamInfo paramInfo)
	{
		uniforms.push_back(paramInfo);
	}

	void EmplaceUniform(EShaderParamType type, std::string name)
	{
		size_t sizeOfParam = SizeOfParam(type);
		uniforms.emplace_back(type, name, sizeOfShader);
		sizeOfShader += sizeOfParam;
	}
};