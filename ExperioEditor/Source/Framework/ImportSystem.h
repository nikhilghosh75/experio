#pragma once
#include <functional>
#include <string>
#include "Runtime/Files/FFileCategory.h"

struct FImportInfo
{
	std::string filepath;
	
	FImportInfo();

	EAssetType AssetType();

	FFileCategory FileCategory();
};

enum class EImportHandlerResult
{
	Handled,
	NotHandled,
	Failed
};

class ImportScriptManager
{
public:
	std::vector<std::function<EImportHandlerResult(FImportInfo)>> importFunctions;
};

class ImportSystem
{
public:
	static ImportScriptManager* manager;

	static void Initialize();

	static void Import(const std::string& fromFilepath, const std::string& toDirectory);

private:
	static bool RejectAssetType(EAssetType type);
};

class ImportRegisterer
{
public:
	ImportRegisterer(std::function<EImportHandlerResult(FImportInfo)> func)
	{
		if (ImportSystem::manager == nullptr)
		{
			ImportSystem::manager = new ImportScriptManager();
		}
		ImportSystem::manager->importFunctions.push_back(func);
	}
};

#define IMPORT_FUNCTION(_funcName_) ImportRegisterer _funcName_register(##_funcName_);