#include "FFileCategory.h"
#include "LFileOperations.h"

FFileCategory::FFileCategory()
{
	this->type = EAssetType::Unknown;
	this->isMeta = false;
}

FFileCategory::FFileCategory(std::string s)
{
	this->type = LFileOperations::GetFileType(s);
	if (this->type == EAssetType::Meta)
	{
		this->isMeta = true;
		this->type = LFileOperations::GetFileTypeOfMeta(s);
	}
}

bool FFileCategory::IsCode() const
{
	return this->type == EAssetType::CPP || this->type == EAssetType::H || this->type == EAssetType::NonEngineCode;
}

bool FFileCategory::IsParseable() const
{
	return this->type == EAssetType::Font
		|| this->type == EAssetType::Image
		|| this->type == EAssetType::Material
		|| this->type == EAssetType::Mesh
		|| this->type == EAssetType::Scene;
}

bool FFileCategory::IsEngineOnly() const
{
	return this->type == EAssetType::Material
		|| this->type == EAssetType::Particle
		|| this->type == EAssetType::Scene
		|| this->type == EAssetType::Shader;
}
