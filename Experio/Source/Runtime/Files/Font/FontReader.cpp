#include "FontReader.h"
#include "FNTReader.h"
#include "../LFileOperations.h"
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
