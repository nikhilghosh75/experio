#include "ImportSystem.h"
#include <filesystem>
#include "Runtime/Files/LFileOperations.h"
namespace fs = std::filesystem;

ImportScriptManager* ImportSystem::manager;

void ImportSystem::Import(const std::string & fromFilepath, const std::string & toDirectory)
{
	EAssetType type = LFileOperations::GetFileType(fromFilepath);
	if (RejectAssetType(type))
	{
		return;
	}

	std::string stripFilename = LFileOperations::StripFilename(fromFilepath);
	fs::copy(fromFilepath, toDirectory + "/" + stripFilename);
	
	FImportInfo info;
	info.filepath = toDirectory + "/" + stripFilename;

	for (size_t i = 0; i < manager->importFunctions.size(); i++)
	{
		EImportHandlerResult result = manager->importFunctions[i](info);
		if (result != EImportHandlerResult::NotHandled) break;
	}
}

bool ImportSystem::RejectAssetType(EAssetType type)
{
	return type == EAssetType::Meta || type == EAssetType::NonEngineCode;
}

FImportInfo::FImportInfo()
{
}

EAssetType FImportInfo::AssetType()
{
	return EAssetType();
}

FFileCategory FImportInfo::FileCategory()
{
	return FFileCategory();
}
