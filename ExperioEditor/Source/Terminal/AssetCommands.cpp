#include "TerminalCommands.h"
#include "../Framework/AssetManager.h"
#include <sstream>

int NumAssets(const std::vector<std::string>& args)
{
	if (args.size() == 1)
	{
		NumAssets({ "", "-d" });
		NumAssets({ "", "-f" });
		NumAssets({ "", "-i" });
		NumAssets({ "", "-m" });
		NumAssets({ "", "-s" });
		return 0;
	}

	size_t numAssets = 0;
	std::string type = "Unknown Assets";
	switch (args[1][1])
	{
	case 'd': numAssets = AssetManager::NumFilesOfType(EAssetType::Data); type = "Datatables"; break;
	case 'f': numAssets = AssetManager::NumFilesOfType(EAssetType::Font); type = "Fonts"; break;
	case 'i': numAssets = AssetManager::NumFilesOfType(EAssetType::Image); type = "Images"; break;
	case 'm': numAssets = AssetManager::NumFilesOfType(EAssetType::Mesh); type = "Meshes"; break;
	case 's': numAssets = AssetManager::NumFilesOfType(EAssetType::Scene); type = "Scenes"; break;
	}

	std::stringstream ss;
	ss << numAssets << " " << type << " found.";
	Terminal::Print(ss.str());

	return 0;
}