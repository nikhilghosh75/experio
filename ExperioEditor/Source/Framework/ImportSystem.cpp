#include "ImportSystem.h"
#include "MetaSystem.h"
#include "../Import Scripts/ImportScripts.h"
#include <filesystem>
#include "Runtime/Files/LFileOperations.h"
namespace fs = std::filesystem;

ImportScriptManager* ImportSystem::manager;

void ImportSystem::Initialize()
{
	manager->importFunctions.push_back(std::function<EImportHandlerResult(FImportInfo)>(ImportMTL));
	manager->importFunctions.push_back(std::function<EImportHandlerResult(FImportInfo)>(ImportOBJ));
}

void ImportSystem::Shutdown()
{
	delete manager;
}

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

	MetaSystem::GenerateMetaFile(info.filepath);
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
