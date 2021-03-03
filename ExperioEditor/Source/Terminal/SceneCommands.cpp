#include "TerminalCommands.h"
#include "../Core/EditorApplication.h"
#include "Runtime/Containers/LString.h"
#include "Runtime/Framework/Scene.h"
#include "Runtime/Framework/SceneLoader.h"

/*
Example usage:
	load-scene Assets/Scenes/TestScene.pbscene
	load-scene Assets/Scenes/TestScene.pbscene 2
*/

int LoadScene(const std::vector<std::string>& args)
{
	if (args.size() == 1 || args.size() > 3)
	{
		return INVALID_ARG_COUNT;
	}

	std::string fullFilepath = EditorApplication::GetFullFilePath(args[1]);

	uint8_t indexToLoad = 0;
	if (args.size() == 3)
	{
		indexToLoad = LString::StringToUByte(args[2]);
		if (indexToLoad > MAX_SCENES)
		{
			Terminal::Print("Load index is an invalid index, can't load");
			return -1;
		}
	}

	bool loaded = SceneLoader::LoadSceneFromFile(fullFilepath, indexToLoad);
	if (loaded)
	{
		Terminal::Print("Scene successfully loaded");
	}
	else
	{
		Terminal::Print("Scene could not be loaded");
	}

	return 0;
}