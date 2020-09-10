#pragma once
#include <string>
#include <stdint.h>
#include <filesystem>
#include "FFileCategory.h"
#include "../Time/FDateTime.h"

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

class LFileOperations
{
public:
	static float BytesToMultiple(uint64_t bytes, EDataUnit unit);

	static std::string BytesToString(uint64_t bytes, int sigFigs, bool truncate = false);

	static bool DoesFileHaveExtension(std::string filePath, const char* extension);

	static std::string GetExtension(std::string filePath);

	static std::string GetFullFilePath(std::string filePath);

	static EAssetType GetFileType(std::string filePath);

	static EAssetType GetFileTypeOfMeta(std::string filePath);

	static EAssetType GetFileTypeOfExt(std::string ext);

	constexpr static uint64_t MultipleToBytes(float bytes, EDataUnit unit);
};