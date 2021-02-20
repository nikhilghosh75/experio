#include "MetaSystem.h"
#include "AssetManager.h"
#include "../CodeParser/LCodeParser.h"
#include "Runtime/Data/Datatable.h"
#include "Runtime/Files/Data/DataReader.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Rendering/Shaders/ShaderReader.h"
#include <filesystem>

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

	while (inFile >> key)
	{
		inFile.getline(value.data(), value.capacity());
		metadata.entries.emplace_back(key, value);
	}

	return metadata;
}

void MetaSystem::GenerateMetaFile(const std::string & filepath)
{
	std::string metaFilepath = filepath + ".meta";
	EAssetType type = LFileOperations::GetFileType(filepath);

	std::ofstream outFile;
	outFile << "Type: " << LFileOperations::AssetTypeToString(type) << std::endl;
	outFile << "ID: " << Experio::GUID::Random().ToString() << std::endl;
	outFile << "SerializedSize: " << AssetManager::SerializedSizeOf(filepath) << std::endl;
	
	GenerateMetadata(filepath, outFile, type);
}

void MetaSystem::GenerateMetadata(const std::string & filepath, std::ofstream & outFile, EAssetType type)
{
	switch (type)
	{
	case EAssetType::CPP: CppMetadata(filepath, outFile); break;
	case EAssetType::Font: FontMetadata(filepath, outFile); break;
	case EAssetType::H: CppMetadata(filepath, outFile); break;
	case EAssetType::Image: ImageMetadata(filepath, outFile); break;
	case EAssetType::NonEngineCode: NonEngineMetadata(filepath, outFile); break;
	case EAssetType::Particle: ParticleMetadata(filepath, outFile); break;
	case EAssetType::Scene: SceneMetadata(filepath, outFile); break;
	case EAssetType::Shader: ShaderMetadata(filepath, outFile); break;
	}
}

void MetaSystem::CppMetadata(const std::string & filepath, std::ofstream & outFile)
{
	// TO-DO: Get CPP File Type
}

void MetaSystem::FontMetadata(const std::string & filepath, std::ofstream & outFile)
{
	// Is the image stored in the font file. Depends on the extension
	bool imageStored = false;
	std::string ext = LFileOperations::GetExtension(filepath);
	if (ext == "otf" || ext == "ttf")
		imageStored = true;

	outFile << "ImageStored: " << LString::BoolToString(imageStored) << std::endl;
}

void MetaSystem::ImageMetadata(const std::string & filepath, std::ofstream & outFile)
{
	std::string compression = "None";
	std::string ext = LFileOperations::GetExtension(filepath);
	if (ext == "png")
		compression = "Deflate";

	outFile << "Compression: " << compression << std::endl;
}

void MetaSystem::NonEngineMetadata(const std::string & filepath, std::ofstream & outFile)
{
	ECodingLanguage language = LCodeParser::FilepathToLanguage(filepath);
	outFile << "Language: " << LCodeParser::LanguageToString(language) << std::endl;
}

void MetaSystem::ParticleMetadata(const std::string & filepath, std::ofstream & outFile)
{
	outFile << "Version: " << "1" << std::endl;
}

void MetaSystem::SceneMetadata(const std::string & filepath, std::ofstream & outFile)
{
	outFile << "Version: " << "1" << std::endl;
}

void MetaSystem::ShaderMetadata(const std::string & filepath, std::ofstream & outFile)
{
	FShaderDataInternal data = ShaderReader::ParseShader(filepath);
	
	outFile << "Language: " << ShaderReader::LanguageToString(data.language) << std::endl;
}
