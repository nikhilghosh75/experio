#include "FontReader.h"
#include "BinFontReader.h"
#include "LFontOperations.h"
#include "FNTReader.h"
#include "TTFReader.h"
#include "../LFileOperations.h"
#include "../../Debug/Debug.h"
#include "../../Framework/AssetMap.h"
#include "../../Rendering/Managers/FontManager.h"

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

std::vector<FFontVariant> FontReader::ReadVariantsFromMeta(const char* filename)
{
	std::vector<FFontVariant> variants;

	std::string metaFilename = LFileOperations::GetMetaFilename(filename);
	std::ifstream inMeta(metaFilename);

	char buffer[64];

	for (int i = 0; i < 10; i++)
		inMeta.getline(buffer, 64);

	int numVariants = 0;
	inMeta >> buffer >> numVariants;

	if (numVariants == 0)
		return variants;

	for (int i = 0; i < numVariants; i++)
	{
		FFontVariant variant;
		
		std::string variantTypeStr;
		inMeta >> buffer >> variantTypeStr;
		variant.type = LFontOperations::StringToFontType(variantTypeStr);
		
		std::string variantIdStr;
		inMeta >> buffer >> variantIdStr;
		Experio::GUID variantGuid(variantIdStr);
		std::string variantFilepath;
		bool foundVariant = AssetMap::guidMap.SafeGet(variantGuid, variantFilepath);
		
		if (foundVariant)
		{
			LFileOperations::CorrectFilepath(variantFilepath);
			variant.dataIndex = FontManager::LoadFont(variantFilepath, true).fontID;
			variant.loaded = true;

			variants.push_back(variant);
		}
	}

	return variants;
}
