#pragma once
#include <string>
#include "Runtime/Files/FFileCategory.h"

class ImportSystem
{
public:
	static void Import(const std::string& fromFilepath, const std::string& toDirectory);

private:
	static bool RejectAssetType(EAssetType type);
};