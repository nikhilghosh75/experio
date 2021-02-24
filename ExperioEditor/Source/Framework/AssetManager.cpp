#include "AssetManager.h"
#include "MetaSystem.h"
#include "../Core/EditorApplication.h"
#include "../Files/SceneConverter.h"
#include "Runtime/Files/FFileCategory.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Files/Font/FontReader.h"
#include "Runtime/Files/Mesh/MeshReader.h"
#include <filesystem>
namespace fs = std::filesystem;

THashtable<Experio::GUID, std::string, Experio::GUIDHashFunction> AssetManager::foundGuids;

void AssetManager::Copy(const std::string & from, const std::string & to)
{
	if (LFileOperations::DoesFileHaveExtension(from, "meta"))
		return;

	fs::copy(from, to);
	MetaSystem::GenerateMetaFile(to);

	// Add new GUID to foundGuids
	std::ifstream inFile(from + ".meta");
	std::string str;
	inFile >> str >> str >> str >> str; // GUID will always be the first one

	Experio::GUID guid(str);
	foundGuids.Set(guid, to);
}

Experio::GUID AssetManager::FilenameToGUID(const std::string & filename)
{
	if (LFileOperations::DoesFileHaveExtension(filename, "meta"))
	{
		// If is meta, read it
		std::ifstream inFile(filename);
		std::string str;
		inFile >> str >> str >> str >> str; // GUID will always be the first one

		// Insert GUID into found guids
		Experio::GUID guid(str);
		std::string realFilename = filename.substr(0, filename.size() - 5);
		foundGuids.Insert(guid, realFilename);
		return guid;
	}
	// If is not meta, return this function of the meta file
	return FilenameToGUID(filename + ".meta");
}

BuildSizeDetails AssetManager::GetBuildSizeDetails()
{
	BuildSizeDetails details;

	for (auto& p : fs::recursive_directory_iterator(EditorApplication::assetsFilePath))
	{
		EAssetType type = LFileOperations::GetFileType(p.path().string());
		size_t size = SerializedSizeOf(p.path().string());

		switch (type)
		{
		case EAssetType::Data: details.datatableSize += size; break;
		case EAssetType::Font: details.fontSize += size; break;
		case EAssetType::Image: details.imageSize += size; break;
		case EAssetType::Mesh: details.meshSize += size; break;
		case EAssetType::Particle: details.particleSize += size; break;
		case EAssetType::Prefab: details.prefabSize += size; break;
		case EAssetType::Scene: details.sceneSize += size; break;
		case EAssetType::Text: details.textSize += size; break;
		}
	}

	return details;
}

std::string AssetManager::GUIDToFilename(Experio::GUID guid)
{
	std::string filename;
	if (foundGuids.SafeGet(guid, filename))
	{
		return filename;
	}

	return "NotFound";
}

bool AssetManager::IsIncludedInBuild(const std::string & str)
{
	// Fix this later when optional files are implemented
	return true;
}

void AssetManager::Rename(const std::string & from, const std::string & to)
{
	if (LFileOperations::DoesFileHaveExtension(from, "meta"))
		return;

	Experio::GUID guid = FilenameToGUID(from + ".meta");
	fs::rename(from, to);
	fs::rename(from + ".meta", to + ".meta");
	foundGuids.Set(guid, to);
}

void AssetManager::Populate()
{
	PopulateFromDirectory(EditorApplication::assetsFilePath);
	PopulateFromDirectory(EditorApplication::editorFilePath);
	PopulateFromDirectory(EditorApplication::sourceFilePath);
}

size_t AssetManager::SizeOf(const std::string & filename)
{
	return fs::file_size(filename);
}

size_t AssetManager::SizeOfBuild()
{
	size_t buildSize = 0;

	for (auto& p : fs::recursive_directory_iterator(EditorApplication::assetsFilePath))
	{
		buildSize += SerializedSizeOf(p.path().string());
	}

	return buildSize;
}

size_t AssetManager::SerializedSizeOf(const std::string & filename)
{
	EAssetType type = LFileOperations::GetFileType(filename);
	
	switch (type)
	{
	// To-Do: Calculate Symbols of Cpp File
	case EAssetType::CPP: return 0;
	case EAssetType::Directory: return 0;
	case EAssetType::Font: return FontReader::SerializedSizeOf(filename.c_str());
	case EAssetType::H: return 0;
	case EAssetType::Markup: return 0;
	case EAssetType::Mesh: return MeshReader::SerializedSizeOf(filename.c_str());
	case EAssetType::Meta: return 0;
	case EAssetType::NonEngineCode: return 0;
	case EAssetType::Scene: return SceneConverter::SerializedSizeOfScene(filename);
	case EAssetType::Style: return 0;
	}

	// NOTE: Image Serialization will be determined later
	return std::filesystem::file_size(filename);
}

bool AssetManager::WillFileBeConverted(const std::string & filename)
{
	EAssetType type = LFileOperations::GetFileType(filename);

	switch (type)
	{
	case EAssetType::Font: return true;
	case EAssetType::Material: return true;
	case EAssetType::Mesh: return true;
	}

	return false;
}

void AssetManager::PopulateFromDirectory(const std::string & str)
{
	fs::recursive_directory_iterator it(str);

	for (auto& p : it)
	{
		if (p.path().extension().string() == "meta")
		{
			std::string pathString = p.path().string();
			std::ifstream inFile(pathString);
			std::string str;
			inFile >> str >> str >> str >> str; // GUID will always be the first one

			// Insert GUID into found guids
			Experio::GUID guid(str);
			std::string realFilename = pathString.substr(0, pathString.size() - 5);
			foundGuids.Insert(guid, realFilename);
		}
	}
}
