#include "DataReader.h"
#include "CSVReader.h"
#include "../LFileOperations.h"
#include "../../Debug/Debug.h"
#include "../../Framework/AssetMap.h"

Datatable * DataReader::ReadFile(const char* filepath)
{
	std::string extension = LFileOperations::GetExtension(filepath);

	if (extension == "csv")
	{
		CSVReader reader;
		return reader.ReadFile(filepath);
	}

	Debug::LogError("Data File was not recognized");
	return nullptr;
}

Datatable * DataReader::ReadFile(unsigned int assetIndex)
{
	std::string filepath;
	if (AssetMap::assetMap.SafeGet(assetIndex, filepath))
	{
		return DataReader::ReadFile(filepath.c_str());
	}
	return nullptr;
}
