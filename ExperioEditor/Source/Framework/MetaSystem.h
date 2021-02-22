#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Runtime/Files/FFileCategory.h"
#include "Runtime/Framework/GUID.h"

enum class ECodeClassBase;

class MetadataEntry
{
public:
	std::string key;
	std::string value;

	MetadataEntry();

	MetadataEntry(const std::string& key, const std::string& value);
};

class Metadata
{
public:
	EAssetType type;
	Experio::GUID guid;
	size_t serializedSize;
	std::vector<MetadataEntry> entries;

	Metadata();
	
	Metadata(EAssetType type, Experio::GUID guid, size_t size, size_t serializedSize);

	std::string& operator[](const std::string& key);
	const std::string& operator[](const std::string& key) const;
};

class MetaSystem
{
public:
	static Metadata ReadMetadata(const std::string& filepath);

	static void GenerateMetaFile(const std::string& filepath);

private:
	static void GenerateMetadata(const std::string& filepath, std::ofstream& outFile, EAssetType type);

	static void CppMetadata(const std::string& filepath, std::ofstream& outFile);

	static void FontMetadata(const std::string& filepath, std::ofstream& outFile);

	static void ImageMetadata(const std::string& filepath, std::ofstream& outFile);

	static void NonEngineMetadata(const std::string& filepath, std::ofstream& outFile);

	static void ParticleMetadata(const std::string& filepath, std::ofstream& outFile);

	static void SceneMetadata(const std::string& filepath, std::ofstream& outFile);

	static void ShaderMetadata(const std::string& filepath, std::ofstream& outFile);

	// This needs to be moved later
	static ECodeClassBase GetCodeClassBase(const std::string& filepath);
};