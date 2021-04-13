#include "FontReader.h"
#include "BinFontReader.h"
#include "FNTReader.h"
#include "TTFReader.h"
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
	else if (extension == "ttf")
	{
		TTFReader reader;
		return reader.ReadFile(fileName);
	}
	else if (extension == "pbbfont")
	{
		BinFontReader reader;
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

size_t FontReader::SerializedSizeOf(const char * filename)
{
	std::string extension = LFileOperations::GetExtension(filename);

	if (extension == "fnt")
	{
		FNTReader reader;
		return reader.SerializedSizeOf(filename);
	}
	else if (extension == "ttf")
	{
		TTFReader reader;
		return reader.SerializedSizeOf(filename);
	}
	else if (extension == "pbbfont")
	{
		BinFontReader reader;
		return reader.SerializedSizeOf(filename);
	}

	Debug::LogError("Font File was not recognized");
	return 0;
}

size_t FontReader::SerializedSizeOf(unsigned int assetIndex)
{
	std::string filepath;
	if (AssetMap::assetMap.SafeGet(assetIndex, filepath))
	{
		return FontReader::SerializedSizeOf(filepath.c_str());
	}
	return 0;
}
