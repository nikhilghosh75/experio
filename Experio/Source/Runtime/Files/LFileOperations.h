#pragma once
#include <string>
#include <stdint.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include "FFileCategory.h"
#include "FileBuffer.h"
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
	static std::string AssetTypeToString(EAssetType type);

	static float BytesToMultiple(uint64_t bytes, EDataUnit unit);

	static std::string BytesToString(uint64_t bytes, int sigFigs, bool truncate = false);

	static TTypedTree<std::filesystem::directory_entry>* CreateFileTree(
		std::string directoryRoot, EFileTreeOptions options = EFileTreeOptions::DisplayDirectoriesAndFiles);

	static TTypedTree<std::string>* CreateFileNamesTree(
		std::string directoryRoot, EFileTreeOptions options = EFileTreeOptions::DisplayDirectoriesAndFiles);

	static bool DoesFileHaveExtension(std::string filePath, const char* extension);

	static FDateTime FiletimeToDateTime(std::filesystem::file_time_type time);

	static std::vector<std::string> GetAllFilepathsOfExt(const std::string& root, const char* extension);

	static std::string GetDirectory(const std::string& filePath);

	static std::string GetExtension(const std::string& filePath);

	static std::string GetFullFilePath(std::string filePath);

	static std::string GetFileName(std::filesystem::directory_entry entry);

	static EAssetType GetFileType(const std::string& filePath);

	static EAssetType GetFileTypeOfMeta(std::string filePath);

	static EAssetType GetFileTypeOfExt(std::string ext);

	constexpr static uint64_t MultipleToBytes(float bytes, EDataUnit unit);

	static uint32_t NumFilesInFolder(const std::string& filepath, bool shouldIncludeMetas = false);

	static uint32_t NumFilesInFolderOfType(const std::string& filepath, const std::string& ext);

	static uint32_t NumFilesInFolderRecursive(const std::string& filepath, bool shouldIncludeMetas = false);

	static uint32_t NumFilesInFolderOfTypeRecursive(const std::string& filepath, const std::string& ext);

	static FileBuffer ReadFileToBuffer(std::ifstream& stream, size_t maxLineLength = 512);
	static FileBuffer ReadTrimmedFileToBuffer(std::ifstream& stream);

	static EAssetType StringToAssetType(const std::string& str);

	static std::string StripFilename(const std::string& filename);
	static std::string StripFilename(const std::filesystem::directory_entry& entry);
	static std::string StripFilename(const std::filesystem::path& path);

	static std::string StripFilenameAndExt(const std::string& filename);
};