#pragma once
#include "Runtime/Containers/THashtable.h"
#include "Runtime/Framework/GUID.h"
#include <string>

class AssetManager
{
	static THashtable<Experio::GUID, std::string, Experio::GUIDHashFunction> foundGuids;

public:
	static void Copy(const std::string& from, const std::string& to);

	static Experio::GUID FilenameToGUID(const std::string& str);

	static std::string GUIDToFilename(Experio::GUID guid);

	static bool IsIncludedInBuild(const std::string& str);

	static void Populate();

	static void Rename(const std::string& from, const std::string& to);

	static size_t SizeOf(const std::string& filename);

	static size_t SerializedSizeOf(const std::string& filename);

	static bool WillFileBeConverted(const std::string& filename);

private:
	static void PopulateFromDirectory(const std::string& str);
};