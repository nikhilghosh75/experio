#include "LFileOperations.h"
#include "../Debug/Debug.h"
#include "../Containers/LString.h"
#include <sstream>
#include <iomanip>

float LFileOperations::BytesToMultiple(uint64_t bytes, EDataUnit unit)
{
	switch (unit)
	{
	case EDataUnit::Byte:
		return (float)bytes;
	case EDataUnit::Kilobyte:
		return (float)bytes / 1000.f;
	case EDataUnit::Kibibyte:
		return (float)bytes / 1024.f;
	case EDataUnit::Megabyte:
		return (float)bytes / 1000000.f;
	case EDataUnit::Mebibyte:
		return (float)bytes / 1048576.f;
	case EDataUnit::Gigabyte:
		return (float)bytes / 1000000000.f;
	case EDataUnit::Gigibyte:
		return (float)bytes / 1073741824.f;
	case EDataUnit::Terabyte:
		return (float)bytes / 1000000000000.f;
	case EDataUnit::Tebibyte:
		return (float)bytes / 1099511627776.f;
	case EDataUnit::Petabyte:
		return (float)bytes / 1000000000000000.f;
	case EDataUnit::Pebibyte:
		return (float)bytes / 1125899906842624.f;
	}
	return 0.0f;
}

std::string LFileOperations::BytesToString(uint64_t bytes, int sigFigs, bool truncate)
{
	if (truncate)
	{
		return LString::NumberWithCommas<uint64_t>(bytes) + " B";
	}

	std::stringstream ss;
	if (bytes > 1000000000000000)
	{
		ss << LString::FloatToString(BytesToMultiple(bytes, EDataUnit::Petabyte)) << " PB";
		return ss.str();
	}
	if (bytes > 1000000000000)
	{
		ss << LString::FloatToString(BytesToMultiple(bytes, EDataUnit::Terabyte)) << " TB";
		return ss.str();
	}
	if (bytes > 1000000000)
	{
		ss << LString::FloatToString(BytesToMultiple(bytes, EDataUnit::Gigabyte)) << " GB";
		return ss.str();
	}
	if (bytes > 1000000)
	{
		ss << LString::FloatToString(BytesToMultiple(bytes, EDataUnit::Megabyte)) << " MB";
		return ss.str();
	}
	if (bytes > 1000)
	{
		ss << LString::FloatToString(BytesToMultiple(bytes, EDataUnit::Kilobyte)) << " kB";
		return ss.str();
	}
	return std::to_string(bytes) + " B";
}

bool LFileOperations::DoesFileHaveExtension(std::string filePath, const char * extension)
{
	int indexOfDot = 0;

	for (int i = filePath.size() - 2; i >= 2; i--)
	{
		if (filePath[i] == '.')
		{
			indexOfDot = i;
			break;
		}
	}

	return strcmp(&filePath[indexOfDot + 1], extension) == 0;
}

std::string LFileOperations::GetExtension(std::string filePath)
{
	int indexOfDot = 0;

	for (int i = filePath.size() - 2; i >= 2; i--)
	{
		if (filePath[i] == '.')
		{
			indexOfDot = i;
			break;
		}
	}

	return filePath.substr(indexOfDot + 1);
}

std::string LFileOperations::GetFullFilePath(std::string filePath)
{
	if (filePath[0] == ' ')
	{
		filePath = filePath.substr(1);
	}

	if (filePath[0] == '?')
	{
		if (filePath.find("?Standard?") != std::string::npos)
		{
			return "C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard" + filePath.substr(10);
		}
	}
	return "C:/Users/debgh/source/repos/project-bloo/" + filePath;
}

EAssetType LFileOperations::GetFileType(std::string filePath)
{
	// TO-DO: Add check for directory
	std::string ext = GetExtension(filePath);
	return GetFileTypeOfExt(ext);
}

#define PB_COMPARE_EXT(_string_, _type_) if(ext == _string_)\
{\
	return _type_;\
}\

EAssetType LFileOperations::GetFileTypeOfExt(std::string ext)
{
	PB_COMPARE_EXT("meta", EAssetType::Meta);

	// Anim
	PB_COMPARE_EXT("anim", EAssetType::Animation);

	// Audio
	PB_COMPARE_EXT("wav", EAssetType::Audio);
	PB_COMPARE_EXT("mp3", EAssetType::Audio);

	// CPP
	PB_COMPARE_EXT("cpp", EAssetType::CPP);

	//Data
	PB_COMPARE_EXT("csv", EAssetType::Data);
	PB_COMPARE_EXT("xlsx", EAssetType::Data);

	// TO-DO: Database
	// Font
	PB_COMPARE_EXT("fnt", EAssetType::Font);
	PB_COMPARE_EXT("otf", EAssetType::Font);
	PB_COMPARE_EXT("ttf", EAssetType::Font);

	// H
	PB_COMPARE_EXT("h", EAssetType::H);

	// Image
	PB_COMPARE_EXT("bmp", EAssetType::Image);
	PB_COMPARE_EXT("dds", EAssetType::Image);
	PB_COMPARE_EXT("jpeg", EAssetType::Image);
	PB_COMPARE_EXT("png", EAssetType::Image);
	PB_COMPARE_EXT("tga", EAssetType::Image);

	// Material
	PB_COMPARE_EXT("material", EAssetType::Material);
	
	// Mesh
	PB_COMPARE_EXT("obj", EAssetType::Mesh);
	PB_COMPARE_EXT("fbx", EAssetType::Mesh);

	// Non-Engine Code
	PB_COMPARE_EXT("java", EAssetType::NonEngineCode);
	PB_COMPARE_EXT("cs", EAssetType::NonEngineCode);
	PB_COMPARE_EXT("js", EAssetType::NonEngineCode);

	// TO-DO: Particles
	// Prefab
	PB_COMPARE_EXT("prefab", EAssetType::Prefab);

	// Shader
	PB_COMPARE_EXT("shader", EAssetType::Shader);

	// Scene
	PB_COMPARE_EXT("pbscene", EAssetType::Scene);

	// Text
	PB_COMPARE_EXT("txt", EAssetType::Text);

	// Video
	PB_COMPARE_EXT("mp4", EAssetType::Video);
	PB_COMPARE_EXT("webm", EAssetType::Video);

	return EAssetType::Unknown;
}

EAssetType LFileOperations::GetFileTypeOfMeta(std::string filePath)
{
	Debug::LogError("GetFileTypeOfMeta has not been implemented yet");
	return EAssetType::Unknown;
}

constexpr uint64_t LFileOperations::MultipleToBytes(float bytes, EDataUnit unit)
{
	switch (unit)
	{
	case EDataUnit::Byte:
		return (uint64_t)bytes;
	case EDataUnit::Kilobyte:
		return (uint64_t)(bytes * 1000);
	case EDataUnit::Kibibyte:
		return (uint64_t)(bytes * 1024);
	case EDataUnit::Megabyte:
		return (uint64_t)(bytes * 1000000);
	case EDataUnit::Mebibyte:
		return (uint64_t)(bytes * 1048576);
	case EDataUnit::Gigabyte:
		return (uint64_t)(bytes * 1000000000);
	case EDataUnit::Gigibyte:
		return (uint64_t)(bytes * 1073741824);
	case EDataUnit::Terabyte:
		return (uint64_t)(bytes * 1000000000000);
	case EDataUnit::Tebibyte:
		return (uint64_t)(bytes * 1099511627776);
	case EDataUnit::Petabyte:
		return (uint64_t)(bytes * 1000000000000000);
	case EDataUnit::Pebibyte:
		return (uint64_t)(bytes * 1125899906842624);
	}
	return 0;
}