#include "FontReader.h"
#include "FNTReader.h"
#include "../LFileOperations.h"
#include "../../Framework/AssetMap.h"
#include "../../Debug/Debug.h"

FontData * FontReader::ReadFile(const char * fileName)
{
	std::string extension = LFileOperations::GetExtension(fileName);

	if (extension == "fnt")
	{
		FNTReader reader;
		return reader.ReadFile(fileName);
	}

	Debug::LogError("Font File was not recognized");
	return nullptr;
}

FontData * FontReader::ReadFile(unsigned int assetIndex)
{
	std::string filepath;
	if (AssetMap::assetMap.SafeGet(assetIndex, filepath))
	{
		return FontReader::ReadFile(filepath.c_str());
	}
	return nullptr;
}
