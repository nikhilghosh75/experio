#include "LFileOperations.h"
#include "../Debug/Debug.h"
#include "../Containers/LString.h"
#include "../Framework/Project.h"
#include <sstream>
#include <iomanip>
#include <chrono>
namespace fs = std::filesystem;

std::string LFileOperations::AssetTypeToString(EAssetType type)
{
	switch (type)
	{
	case EAssetType::Animation: return "Animation";
	case EAssetType::Audio: return "Audio";
	case EAssetType::CPP: return "C++";
	case EAssetType::Data: return "Data";
	case EAssetType::Directory: return "Directory";
	case EAssetType::Font: return "Font";
	case EAssetType::H: return "H";
	case EAssetType::Image: return "Image";
	case EAssetType::InputMap: return "InputMap";
	case EAssetType::Markup: return "Markup";
	case EAssetType::Material: return "Material";
	case EAssetType::Mesh: return "Mesh";
	case EAssetType::Meta: return "Meta";
	case EAssetType::NonEngineCode: return "NonEngineCode";
	case EAssetType::Particle: return "Particle";
	case EAssetType::Prefab: return "Prefab";
	case EAssetType::Scene: return "Scene";
	case EAssetType::Shader: return "Shader";
	case EAssetType::Soundbank: return "Soundbank";
	case EAssetType::Style: return "Style";
	case EAssetType::Text: return "Text";
	case EAssetType::Video: return "Video";
	}
	return "Unknown";
}

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

void LFileOperations::CorrectFilepath(char* filepath)
{
	size_t i = 0;
	while (filepath[i] != 0)
	{
		if (filepath[i] == '\\')
		{
			filepath[i] = '/';
		}
		i++;
	}
}

void LFileOperations::CorrectFilepath(std::string& filepath)
{
	// Loop through the string and replace all '\\' with '/'
	for (size_t i = 0; i < filepath.size(); i++)
	{
		if (filepath[i] == '\\')
		{
			filepath[i] = '/';
		}
	}
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

	if (extension[0] == '.')
	{
		return strcmp(&filePath[indexOfDot], extension) == 0;
	}
	return strcmp(&filePath[indexOfDot + 1], extension) == 0;
}

FDateTime LFileOperations::FiletimeToDateTime(std::filesystem::file_time_type time)
{
	Debug::LogError("Requires C++ 20 in order to work.");
	return FDateTime();
}

std::vector<std::string> LFileOperations::GetAllFilepathsOfExt(const std::string & root, const char * extension)
{
	std::vector<std::string> files;

	for (auto& p : fs::recursive_directory_iterator(root))
	{
		if (GetExtension(p.path().string()) == extension)
		{
			files.push_back(p.path().string());
		}
	}

	return files;
}

std::string LFileOperations::GetDirectory(const std::string & filePath)
{
	int indexOfSlash = 0;

	for (int i = filePath.size() - 2; i >= 2; i--)
	{
		if (filePath[i] == '\\' || filePath[i] == '/' || filePath[i] == 92)
		{
			indexOfSlash = i;
			break;
		}
	}

	return filePath.substr(0, indexOfSlash);
}

std::string LFileOperations::GetExtension(const std::string& filePath)
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
			return Project::experioResourcesPath + "/Standard" + filePath.substr(10);
		}
		else if (filePath.find("?Assets?") != std::string::npos)
		{
			return Project::projectAssetsPath + filePath.substr(8);
		}
	}
	return filePath;
}

std::string LFileOperations::GetFileName(std::filesystem::directory_entry entry)
{
	return StripFilename(entry.path().string());
}

EAssetType LFileOperations::GetFileType(const std::string& filePath)
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
	PB_COMPARE_EXT("ogg", EAssetType::Audio);
	PB_COMPARE_EXT("mp3", EAssetType::Audio);

	// CPP
	PB_COMPARE_EXT("cpp", EAssetType::CPP);

	//Data
	PB_COMPARE_EXT("pbnumdata", EAssetType::Data);
	PB_COMPARE_EXT("csv", EAssetType::Data);
	PB_COMPARE_EXT("xlsx", EAssetType::Data);

	// Font
	PB_COMPARE_EXT("fnt", EAssetType::Font);
	PB_COMPARE_EXT("otf", EAssetType::Font);
	PB_COMPARE_EXT("ttf", EAssetType::Font);
	PB_COMPARE_EXT("pbbfont", EAssetType::Font);

	// H
	PB_COMPARE_EXT("h", EAssetType::H);
	PB_COMPARE_EXT("hpp", EAssetType::H);

	// Image
	PB_COMPARE_EXT("bmp", EAssetType::Image);
	PB_COMPARE_EXT("dds", EAssetType::Image);
	PB_COMPARE_EXT("jpeg", EAssetType::Image);
	PB_COMPARE_EXT("png", EAssetType::Image);
	PB_COMPARE_EXT("tga", EAssetType::Image);

	// Input Map
	PB_COMPARE_EXT("pbipmap", EAssetType::InputMap);

	// Markup
	PB_COMPARE_EXT("xml", EAssetType::Markup);

	// Material
	PB_COMPARE_EXT("material", EAssetType::Material);
	
	// Mesh
	PB_COMPARE_EXT("obj", EAssetType::Mesh);
	PB_COMPARE_EXT("fbx", EAssetType::Mesh);
	PB_COMPARE_EXT("3ds", EAssetType::Mesh);
	PB_COMPARE_EXT("pbbmesh", EAssetType::Mesh);

	// Non-Engine Code
	PB_COMPARE_EXT("java", EAssetType::NonEngineCode); // Java
	PB_COMPARE_EXT("cs", EAssetType::NonEngineCode); // C#
	PB_COMPARE_EXT("c", EAssetType::NonEngineCode); // C
	PB_COMPARE_EXT("js", EAssetType::NonEngineCode); // Javascript
	PB_COMPARE_EXT("py", EAssetType::NonEngineCode); // Python
	PB_COMPARE_EXT("rs", EAssetType::NonEngineCode); // Rust
	PB_COMPARE_EXT("rlib", EAssetType::NonEngineCode); // Rust
	PB_COMPARE_EXT("r", EAssetType::NonEngineCode); // R
	PB_COMPARE_EXT("swift", EAssetType::NonEngineCode); // Swift

	// Particle
	PB_COMPARE_EXT("pbprtcle", EAssetType::Particle);

	// Prefab
	PB_COMPARE_EXT("prefab", EAssetType::Prefab);

	// Shader
	PB_COMPARE_EXT("shader", EAssetType::Shader);

	// Scene
	PB_COMPARE_EXT("pbbscene", EAssetType::Scene);
	PB_COMPARE_EXT("pbscene", EAssetType::Scene);

	// Soundbank
	PB_COMPARE_EXT("pbbsbnk", EAssetType::Soundbank);
	PB_COMPARE_EXT("pbsbnk", EAssetType::Soundbank);

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

uint32_t LFileOperations::NumFilesInFolder(const std::string & filepath, bool shouldIncludeMetas)
{
	uint32_t numFiles = 0;

	for (auto& p : fs::directory_iterator(filepath))
	{
		std::string pathString = p.path().filename().string();
		EAssetType type = LFileOperations::GetFileType(pathString);

		if (type == EAssetType::Meta && !shouldIncludeMetas)
			continue;

		numFiles++;
	}

	return numFiles;
}

uint32_t LFileOperations::NumFilesInFolderOfType(const std::string & filepath, const std::string & ext)
{
	uint32_t numFiles = 0;

	for (auto& p : fs::directory_iterator(filepath))
	{
		std::string pathString = p.path().filename().string();
		if (LFileOperations::GetExtension(pathString) == ext)
		{
			numFiles++;
		}
	}

	return numFiles;
}

uint32_t LFileOperations::NumFilesInFolderRecursive(const std::string & filepath, bool shouldIncludeMetas)
{
	uint32_t numFiles = 0;

	for (auto& p : fs::recursive_directory_iterator(filepath))
	{
		std::string pathString = p.path().filename().string();
		EAssetType type = LFileOperations::GetFileType(pathString);

		if (type == EAssetType::Meta && !shouldIncludeMetas)
			continue;

		numFiles++;
	}

	return numFiles;
}

uint32_t LFileOperations::NumFilesInFolderOfTypeRecursive(const std::string & filepath, const std::string & ext)
{
	uint32_t numFiles = 0;

	for (auto& p : fs::recursive_directory_iterator(filepath))
	{
		std::string pathString = p.path().filename().string();
		if (LFileOperations::GetExtension(pathString) == ext)
		{
			numFiles++;
		}
	}

	return numFiles;
}

FileBuffer LFileOperations::ReadFileToBuffer(std::ifstream & stream, size_t maxLineLength)
{
	std::stringstream ss;
	char* s = new char[maxLineLength];

	while (stream.getline(s, maxLineLength))
	{
		ss << s << "\n";
	}

	std::string output = ss.str();
	return FileBuffer(output.data(), output.length());
}

FileBuffer LFileOperations::ReadTrimmedFileToBuffer(std::ifstream & stream)
{
	std::stringstream ss;
	std::string s;

	while (stream >> s)
	{
		ss << s << " ";
	}

	std::string output = ss.str();
	return FileBuffer(output.data(), output.length());
}

std::string LFileOperations::ReplaceExtension(const std::string& filepath, const std::string& newExt)
{
	std::string newFilepath = filepath;
	int indexOfDot = 0;

	for (int i = filepath.size() - 2; i >= 2; i--)
	{
		if (filepath[i] == '.')
		{
			indexOfDot = i;
			break;
		}
	}

	newFilepath.replace(indexOfDot + 1, filepath.size() - indexOfDot - 1, newExt);
	
	return newFilepath;
}

EAssetType LFileOperations::StringToAssetType(const std::string & str)
{
	if (str == "Animation") return EAssetType::Animation;
	if (str == "Audio") return EAssetType::Audio;
	if (str == "C++") return EAssetType::CPP;
	if (str == "Data") return EAssetType::Data;
	if (str == "Directory") return EAssetType::Directory;
	if (str == "Font") return EAssetType::Font;
	if (str == "H") return EAssetType::H;
	if (str == "Image") return EAssetType::Image;
	if (str == "InputMap") return EAssetType::InputMap;
	if (str == "Markup") return EAssetType::Markup;
	if (str == "Material") return EAssetType::Material;
	if (str == "Mesh") return EAssetType::Mesh;
	if (str == "Meta") return EAssetType::Meta;
	if (str == "NonEngineCode") return EAssetType::NonEngineCode;
	if (str == "Particle") return EAssetType::Particle;
	if (str == "Prefab") return EAssetType::Prefab;
	if (str == "Scene") return EAssetType::Scene;
	if (str == "Shader") return EAssetType::Shader;
	if (str == "Soundbank") return EAssetType::Soundbank;
	if (str == "Style") return EAssetType::Style;
	if (str == "Text") return EAssetType::Text;
	if (str == "Video") return EAssetType::Video;
	return EAssetType::Unknown;
}

std::string LFileOperations::StripFilename(const std::string& filename)
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

std::string LFileOperations::StripFilename(const std::filesystem::directory_entry& entry)
{
	return entry.path().stem().string();
}

std::string LFileOperations::StripFilename(const std::filesystem::path& path)
{
	return path.stem().string();
}

std::string LFileOperations::StripFilenameAndExt(const std::string& filename)
{
	int indexOfSlash = 0;
	int indexOfPeriod = 0;

	for (int i = filename.size() - 2; i >= 2; i--)
	{
		if (filename[i] == '\\' || filename[i] == '/' || filename[i] == 92)
		{
			indexOfSlash = i;
			break;
		}
		if (filename[i] == '.')
		{
			indexOfPeriod = i;
		}
	}

	return filename.substr(indexOfSlash + 1, indexOfPeriod - indexOfSlash - 1);
}
