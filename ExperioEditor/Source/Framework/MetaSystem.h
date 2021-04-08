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

	bool Empty() const;
};

class MetaSystem
{
public:
	static Metadata ReadMetadata(const std::string& filepath);

	static void GenerateMetaFile(const std::string& filepath);

	static void FixMetafiles();

private:
	static void GenerateMetadata(const std::string& filepath, std::ofstream& outFile, EAssetType type);
};