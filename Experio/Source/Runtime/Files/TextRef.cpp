#include "TextRef.h"
#include "../Framework/AssetMap.h"
#include <filesystem>

TextRef::TextRef()
{
	this->filepath = "";
}

TextRef::TextRef(unsigned int id)
{
	this->filepath = AssetMap::assetMap.Get(id);
}

TextRef::TextRef(const std::string filepath)
{
	this->filepath = filepath;
}

size_t TextRef::FileSize() const
{
	return std::filesystem::file_size(this->filepath);
}
