#include "BuildSystem.h"
#include "AssetMapSaver.h"
#include "CodeGenerator.h"
#include <filesystem>
#include <sstream>
#include <thread>
#include "Runtime/Containers/LString.h"
#include "Runtime/Files/FFileCategory.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Framework/Project.h"
#include "../Core/EditorApplication.h"
#include "../Files/FileConverters.h"

namespace fs = std::filesystem;

extern void RCCCompileProject();

namespace ExperioEditor::BuildSystem
{

static bool isBuilding = false;
static EBuildTarget currentTarget = EBuildTarget::None;
static float currentProgress;
const static float totalProgress = 145;

const static float fileConvertProgress = 70;

static bool isCompiling = false;

void StartBuildForWindows(const std::string & buildFolder, const FWindowsBuildSettings & buildSettings)
{
	isBuilding = true;
	currentTarget = EBuildTarget::Windows;

	std::thread worker(Detail::DoBuildForWindows, buildFolder, buildSettings);
	worker.detach();
}

bool IsBuilding()
{
	return isBuilding;
}

EBuildTarget GetCurrentBuildTarget()
{
	return currentTarget;
}

float GetCurrentProgress()
{
	return currentProgress / totalProgress;
}

FWindowsBuildSettings DefaultWindowsBuildSettings()
{
	return FWindowsBuildSettings();
}

void Detail::DoBuildForWindows(const std::string & buildFolder, const FWindowsBuildSettings & buildSettings)
{
	currentProgress = 0;

	// Step 1: Regenerate All Files
	Detail::RegenerateFiles();

	// Step 2: Recompile Project
	RCCCompileProject();
	Detail::BlockUntilCompilationComplete();
	currentProgress += 40;

	// Step 3: Move Files
	Detail::MoveFilesToBuildFolder(buildFolder);

	// Step 4: Move Executable
	Detail::MoveBuildFiles(buildFolder);
}

void Detail::RegenerateFiles()
{
	CodeGenerator::GenerateComponentManager();
	currentProgress += 5;
	CodeGenerator::GenerateProjectFile();
	currentProgress += 1;
	CodeGenerator::GenerateComponentSerializers();
	currentProgress += 3;
	CodeGenerator::GenerateTagFile();
	currentProgress += 1;
}

void Detail::BlockUntilCompilationComplete()
{
	isCompiling = true;
	CompilationSystem::finishCompilationCallback = HandleCompilationFinish;

	while (isCompiling)
	{

	}
}

void Detail::MoveFilesToBuildFolder(const std::string & buildFolder)
{
	Detail::StartConversion(buildFolder);

	uint32_t numFiles = LFileOperations::NumFilesInFolderRecursive(EditorApplication::assetsFilePath, false);
	currentProgress += 5;

	for (auto& p : fs::recursive_directory_iterator(EditorApplication::assetsFilePath))
	{
		std::string pathString = LString::ReplaceAll(p.path().string(), '/', '\\');
		if (LFileOperations::GetExtension(pathString) == "meta")
			continue;

		Detail::ConvertFile(pathString, buildFolder);
		currentProgress += fileConvertProgress / (float)numFiles;
	}

	Detail::EndConversion(buildFolder);
}

void Detail::StartConversion(const std::string & buildFolder)
{
	// Start Asset Map
	AssetMapSaver::Reset();

	// Start Material Collection
	std::stringstream materialCollection;
	materialCollection << buildFolder << "/collection.pbmatcol";
	uint32_t numMaterials = LFileOperations::NumFilesInFolderOfTypeRecursive(EditorApplication::assetsFilePath, "material");
	MaterialConverter::StartMaterialCollection(materialCollection.str(), numMaterials);
}

void Detail::EndConversion(const std::string & buildFolder)
{
	// End Material Collection
	MaterialConverter::EndMaterialCollection();

	// End Asset Map
	std::stringstream assetMap;
	assetMap << buildFolder << "/map.pbasmap";
	AssetMapSaver::SaveToAssetMap(assetMap.str());
}

void Detail::ConvertFile(const std::string & fromFile, const std::string & toFolder)
{
	EAssetType type = LFileOperations::GetFileType(fromFile);

	if (Detail::ShouldBuildIgnoreCopy(type))
		return;

	std::string toFile = Detail::GetConvertedFilename(fromFile, toFolder, type);
	AssetMapSaver::Insert(toFile);

	switch (type)
	{
	case EAssetType::Font:
		FontConverter::ConvertFontToBinary(fromFile, toFile); break;
	case EAssetType::Material:
		MaterialConverter::MaterialToBinaryMaterial(fromFile); break;
	case EAssetType::Mesh:
		MeshConverter::ConvertMeshToBinary(fromFile, toFile); break;
	// case EAssetType::Scene:
		// SceneConverter::ConvertSceneToBinary(fromFile, toFile); break;
	default:
		fs::copy(fromFile, toFile);
	}
}

bool Detail::ShouldBuildIgnoreCopy(EAssetType type)
{
	return type == EAssetType::Directory || type == EAssetType::Meta
		|| type == EAssetType::Meta || type == EAssetType::Unknown
		|| type == EAssetType::CPP || type == EAssetType::CPP
		|| type == EAssetType::NonEngineCode;
}

std::string Detail::GetConvertedFilename(const std::string & fromFile, const std::string & toFolder, EAssetType type)
{
	std::stringstream toStream;
	toStream << toFolder << "\\" << LFileOperations::StripFilenameAndExt(fromFile);

	switch (type)
	{
	case EAssetType::Font:
		toStream << ".pbbfont"; break;
	case EAssetType::Mesh:
		toStream << ".pbbmesh"; break;
	// case EAssetType::Scene:
		// toStream << ".pbbscene"; break;
	default:
		toStream << "." << LFileOperations::GetExtension(fromFile);
	}

	return toStream.str();
}

void Detail::MoveBuildFiles(const std::string& buildFolder)
{
	std::string dllBuildFolder = EditorApplication::binariesFilePath + "/Intermediate/";
	fs::copy(dllBuildFolder + "Temp.dll", buildFolder + "/Demo Project.dll");
	fs::copy(dllBuildFolder + "Temp.exp", buildFolder + "/Demo Project.exp");
	fs::copy(dllBuildFolder + "Temp.ilk", buildFolder + "/Demo Project.ilk");
	fs::copy(dllBuildFolder + "Temp.lib", buildFolder + "/Demo Project.lib");
	fs::copy(dllBuildFolder + "Temp.pdb", buildFolder + "/Demo Project.pdb");

	Detail::TempMoveExecutable(buildFolder);
}

void Detail::TempMoveExecutable(const std::string& buildFolder)
{
	std::string tempExeFolder = EditorApplication::experioBinariesFilePath + "/x64/Debug/Demo Project/";
	fs::copy(tempExeFolder + "Demo Project_Exe.exe", buildFolder + "/Demo Project_Exe.exe");
	fs::copy(tempExeFolder + "Demo Project_Exe.ilk", buildFolder + "/Demo Project_Exe.ilk");
	fs::copy(tempExeFolder + "Demo Project_Exe.pdb", buildFolder + "/Demo Project_Exe.pdb");
}

void Detail::FinishBuild(EBuildOutcome outcome)
{

}

void Detail::HandleCompilationFinish(FCompilationResult & result)
{
	isCompiling = false;
}

}
