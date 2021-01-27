#pragma once
#include <string>
#include "FFileCategory.h"

class FileRef
{
public:
	FileRef();

	FileRef(unsigned int id);

	FileRef(const std::string filepath);

	std::string filepath;

	EAssetType Type() const;

	FFileCategory Category() const;

	size_t FileSize() const;
};