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
