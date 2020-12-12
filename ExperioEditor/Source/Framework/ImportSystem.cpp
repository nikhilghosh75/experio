#include "ImportSystem.h"
#include <filesystem>
#include "Runtime/Files/LFileOperations.h"
namespace fs = std::filesystem;

void ImportSystem::Import(const std::string & fromFilepath, const std::string & toDirectory)
{
	EAssetType type = LFileOperations::GetFileType(fromFilepath);
	if (RejectAssetType(type))
	{
		return;
	}

	std::string stripFilename = LFileOperations::StripFilename(fromFilepath);
	fs::copy(fromFilepath, toDirectory + "/" + stripFilename);
}

bool ImportSystem::RejectAssetType(EAssetType type)
{
	return type == EAssetType::Meta || type == EAssetType::NonEngineCode;
}
