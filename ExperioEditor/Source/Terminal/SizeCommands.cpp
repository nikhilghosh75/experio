#include "TerminalCommands.h"
#include "TerminalParser.h"
#include "Runtime/Files/LFileOperations.h"
#include "../Framework/AssetManager.h"
#include <sstream>

/*
Example usage:
	sizeof -f Filepath -d
	sizeof -b
	sizeof 'Assets/Meshes/suzanne.obj'
	sizeof 'Assets/Meshes/suzanne.obj' -s
*/

int SizeOf(const std::vector<std::string>& args)
{
	if (args.size() > 3 || args.size() == 1)
	{
		return INVALID_ARG_COUNT;
	}
	std::string filepath = "";

	std::vector<TerminalOption> options = { 
		{'f', "filepath"}, 
		{'b', "build"}, 
		{'d', "detail"}, 
		{'s', "serialized"} 
	};

	bool build = false;
	bool detail = false;
	bool serialized = false;

	for (auto& i : TerminalParser(args, options))
	{
		switch (i.currentOption)
		{
		case 0:
			filepath = i.arg;
			break;
		case 1:
			build = true;
			break;
		case 2:
			detail = true;
			break;
		case 3:
			serialized = true;
			break;
		}
	}

	if (build)
	{
		size_t buildSize = AssetManager::SizeOfBuild();
		if (detail)
		{
			BuildSizeDetails buildDetails = AssetManager::GetBuildSizeDetails();
			// Figure this out later
		}
		std::stringstream ss;
		ss << "Build Size: " << LFileOperations::BytesToString(buildSize, 3);
		Terminal::Print(ss.str());
		return 0;
	}

	size_t size = 0;
	if (serialized)
	{
		size = AssetManager::SizeOf(filepath);
	}
	else
	{
		size = AssetManager::SerializedSizeOf(filepath);
	}

	std::stringstream ss;
	ss << "Size: " << LFileOperations::BytesToString(size, 3);
	Terminal::Print(ss.str());

	return 0;
}