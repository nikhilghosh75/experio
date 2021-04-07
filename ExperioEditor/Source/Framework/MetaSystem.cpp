#include "MetaSystem.h"
#include "AssetManager.h"
#include "CreateMenu.h"
#include "../CodeParser/LCodeParser.h"
#include "../Core/EditorApplication.h"
#include "Metasystem/CppMetasystem.h"
#include "Metasystem/FontMetasystem.h"
#include "Metasystem/ImageMetasystem.h"
#include "Metasystem/ParticleMetasystem.h"
#include "Metasystem/SceneMetasystem.h"
#include "Metasystem/ShaderMetasystem.h"
#include "Runtime/Data/Datatable.h"
#include "Runtime/Files/Data/DataReader.h"
#include "Runtime/Files/LFileOperations.h"
#include <filesystem>
namespace fs = std::filesystem;

MetadataEntry::MetadataEntry()
{
	this->key = "";
	this->value = "";
}

MetadataEntry::MetadataEntry(const std::string & key, const std::string & value)
{
	this->key = key;
	this->value = value;
}

Metadata::Metadata()
{
	this->type = EAssetType::Unknown;
	this->guid = Experio::GUID();
	this->serializedSize = 0;
}

Metadata::Metadata(EAssetType type, Experio::GUID guid, size_t size, size_t serializedSize)
{
	this->type = type;
	this->guid = guid;
	this->serializedSize = serializedSize;
}

std::string & Metadata::operator[](const std::string & key)
{
	for (size_t i = 0; i < entries.size(); i++)
	{
		if (entries[i].key == key)
		{
			return entries[i].value;
		}
	}
	return entries[0].value;
}

const std::string & Metadata::operator[](const std::string & key) const
{
	for (size_t i = 0; i < entries.size(); i++)
	{
		if (entries[i].key == key)
		{
			return entries[i].value;
		}
	}
	return entries[0].value;
}

bool Metadata::Empty() const
{
	return entries.empty();
}

Metadata MetaSystem::ReadMetadata(const std::string & filepath)
{
	std::string realFilepath = filepath;
	if (!LFileOperations::DoesFileHaveExtension(filepath, "meta"))
	{
		realFilepath = filepath + ".meta";
	}

	std::string str;
	std::ifstream inFile(realFilepath);
	Metadata metadata;
	
	inFile >> str >> str;
	metadata.type = LFileOperations::StringToAssetType(str);
	
	inFile >> str >> str;
	metadata.guid = Experio::GUID(str);

	inFile >> str >> metadata.serializedSize;

	std::string key, value;
	key.reserve(32);
	value.reserve(64);

	char spacebar;

	while (inFile >> key)
	{
		inFile.read(&spacebar, 1);
		std::getline(inFile, value);
		key.pop_back(); // Remove ':'
		metadata.entries.emplace_back(key, value);
	}

	return metadata;
}

void MetaSystem::GenerateMetaFile(const std::string & filepath)
{
	std::string metaFilepath = filepath + ".meta";
	EAssetType type = LFileOperations::GetFileType(filepath);

	std::ofstream outFile(metaFilepath);
	outFile << "Type: " << LFileOperations::AssetTypeToString(type) << std::endl;
	outFile << "ID: " << Experio::GUID::Random().ToString() << std::endl;
	outFile << "SerializedSize: " << AssetManager::SerializedSizeOf(filepath) << std::endl;
	
	GenerateMetadata(filepath, outFile, type);
}

void MetaSystem::FixMetafiles()
{
	for (auto& p : fs::recursive_directory_iterator(EditorApplication::assetsFilePath))
	{
		std::string filepath = p.path().string();
		if (LFileOperations::DoesFileHaveExtension(filepath, "meta"))
			continue;

		GenerateMetaFile(filepath);
	}
}

void MetaSystem::GenerateMetadata(const std::string & filepath, std::ofstream & outFile, EAssetType type)
{
	switch (type)
	{
	case EAssetType::CPP: CppMetasystem::GenerateMetadata(filepath, outFile); break;
	case EAssetType::Font: FontMetasystem::GenerateMetadata(filepath, outFile); break;
	case EAssetType::H: CppMetasystem::GenerateMetadata(filepath, outFile); break;
	case EAssetType::Image: ImageMetasystem::GenerateMetadata(filepath, outFile); break;
	case EAssetType::Particle: ParticleMetasystem::GenerateMetadata(filepath, outFile); break;
	case EAssetType::Scene: SceneMetasystem::GenerateMetadata(filepath, outFile); break;
	case EAssetType::Shader: ShaderMetasystem::GenerateMetadata(filepath, outFile); break;
	}
}