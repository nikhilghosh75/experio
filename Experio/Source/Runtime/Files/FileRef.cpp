#include "FileRef.h"
#include "LFileOperations.h"
#include "../Framework/AssetMap.h"
#include <filesystem>

FileRef::FileRef()
{
	this->filepath = "";
}

FileRef::FileRef(unsigned int id)
{
	this->filepath = AssetMap::assetMap.Get(id);
}

FileRef::FileRef(const std::string filepath)
{
	this->filepath = filepath;
}

EAssetType FileRef::Type() const
{
	return LFileOperations::GetFileType(this->filepath);
}

FFileCategory FileRef::Category() const
{
	return FFileCategory(this->filepath);
}

size_t FileRef::FileSize() const
{
	return std::filesystem::file_size(this->filepath);
}
