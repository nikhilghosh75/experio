#pragma once
#include <string>
#include <stdint.h>
#include <filesystem>
#include "FFileCategory.h"
#include "../Time/FDateTime.h"
#include "../Containers/TTypedTree.h"

enum class EDataUnit
{
	Byte,
	Kilobyte,
	Kibibyte,
	Megabyte,
	Mebibyte,
	Gigabyte,
	Gigibyte,
	Terabyte,
	Tebibyte,
	Petabyte,
	Pebibyte
};

enum class EFileTreeOptions
{
	DisplayDirectories = 1,
	DisplayDirectoriesAndFiles = 2
};

class LFileOperations
{
public:
	static float BytesToMultiple(uint64_t bytes, EDataUnit unit);

	static std::string BytesToString(uint64_t bytes, int sigFigs, bool truncate = false);

	static TTypedTree<std::filesystem::directory_entry>* CreateFileTree(
		std::string directoryRoot, EFileTreeOptions options = EFileTreeOptions::DisplayDirectoriesAndFiles);

	static TTypedTree<std::string>* CreateFileNamesTree(
		std::string directoryRoot, EFileTreeOptions options = EFileTreeOptions::DisplayDirectoriesAndFiles);

	static bool DoesFileHaveExtension(std::string filePath, const char* extension);

	static std::string GetExtension(std::string filePath);

	static std::string GetFullFilePath(std::string filePath);

	static std::string GetFileName(std::filesystem::directory_entry entry);

	static EAssetType GetFileType(std::string filePath);

	static EAssetType GetFileTypeOfMeta(std::string filePath);

	static EAssetType GetFileTypeOfExt(std::string ext);

	constexpr static uint64_t MultipleToBytes(float bytes, EDataUnit unit);

	static std::string StripFilename(std::string filename);
	static std::string StripFilename(std::filesystem::directory_entry entry);
	static std::string StripFilename(std::filesystem::path path);
};