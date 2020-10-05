#include "LFileOperations.h"
#include "../Debug/Debug.h"
#include "../Containers/LString.h"
#include <sstream>
#include <iomanip>
namespace fs = std::filesystem;

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

TTypedTree<fs::directory_entry>* LFileOperations::CreateFileTree(std::string directoryRoot, EFileTreeOptions options)
{
	TTypedTree<fs::directory_entry>* tree = new TTypedTree<fs::directory_entry>();
	tree->CreateRoot(fs::directory_entry(directoryRoot));

	fs::recursive_directory_iterator fileIterator(directoryRoot);
	TTypedTreeNode<fs::directory_entry>* current = tree->GetRoot();
	int currentDepth = -1;
	for (auto& p : fileIterator)
	{
		if (!p.is_directory() && options == EFileTreeOptions::DisplayDirectories)
		{
			continue;
		}
		if (currentDepth < fileIterator.depth())
		{
			current->AddChild(p);
			current = current->children[current->children.size() - 1];
		}
		else
		{
			for (int i = 0; i < currentDepth - fileIterator.depth() + 1; i++)
			{
				current = current->parentNode;
			}
			current->AddChild(p);
			current = current->children[current->children.size() - 1];
		}
		currentDepth = fileIterator.depth();
	}

	return tree;
}

TTypedTree<std::string>* LFileOperations::CreateFileNamesTree(std::string directoryRoot, EFileTreeOptions options)
{
	TTypedTree<std::string>* tree = new TTypedTree<std::string>();
	fs::directory_entry root(directoryRoot);
	tree->CreateRoot(root.path().stem().string());

	fs::recursive_directory_iterator fileIterator(directoryRoot);
	TTypedTreeNode<std::string>* current = tree->GetRoot();
	int currentDepth = -1;
	for (auto& p : fileIterator)
	{
		if (!p.is_directory() && options == EFileTreeOptions::DisplayDirectories)
		{
			continue;
		}
		if (currentDepth < fileIterator.depth())
		{
			current->AddChild(p.path().stem().string());
			current = current->children[current->children.size() - 1];
		}
		else
		{
			for (int i = 0; i < currentDepth - fileIterator.depth() + 1; i++)
			{
				current = current->parentNode;
			}
			current->AddChild(p.path().stem().string());
			current = current->children[current->children.size() - 1];
		}
		currentDepth = fileIterator.depth();
	}

	return tree;
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

	if (indexOfDot == 0)
	{
		return "";
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

std::string LFileOperations::GetFileName(std::filesystem::directory_entry entry)
{
	return StripFilename(entry.path().string());
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
	if (ext.size() == 0)
	{
		return EAssetType::Directory;
	}

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
	PB_COMPARE_EXT("hpp", EAssetType::H);

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
	PB_COMPARE_EXT("java", EAssetType::NonEngineCode); // Java
	PB_COMPARE_EXT("cs", EAssetType::NonEngineCode); // C#
	PB_COMPARE_EXT("c", EAssetType::NonEngineCode); // C
	PB_COMPARE_EXT("js", EAssetType::NonEngineCode); // Javascript
	PB_COMPARE_EXT("py", EAssetType::NonEngineCode); // Python
	PB_COMPARE_EXT("rs", EAssetType::NonEngineCode); // Rust
	PB_COMPARE_EXT("rlib", EAssetType::NonEngineCode); // Rust

	// TO-DO: Particles
	// Prefab
	PB_COMPARE_EXT("prefab", EAssetType::Prefab);

	// Shader
	PB_COMPARE_EXT("shader", EAssetType::Shader);

	// Scene
	PB_COMPARE_EXT("pbscene", EAssetType::Scene);

	// Text
	PB_COMPARE_EXT("txt", EAssetType::Text);
	PB_COMPARE_EXT("docx", EAssetType::Text);

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

std::string LFileOperations::StripFilename(std::string filename)
{
	int indexOfSlash = 0;

	for (int i = filename.size() - 2; i >= 2; i--)
	{
		if (filename[i] == '\\' || filename[i] == '/' || filename[i] == 92)
		{
			indexOfSlash = i;
			break;
		}
	}

	return filename.substr(indexOfSlash + 1);
}

std::string LFileOperations::StripFilename(std::filesystem::directory_entry entry)
{
	return entry.path().stem().string();
}

std::string LFileOperations::StripFilename(std::filesystem::path path)
{
	return path.stem().string();
}
