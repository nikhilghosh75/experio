#pragma once
#include <string>
#include <vector>

/// <summary>
/// Represents a collection of sounds that can be loaded all at once.
/// For instance, all the enemies of a game would have their sounds in the same soundbank.
/// </summary>

enum class ESoundbankType
{
	Folder,
	Audio
};

class Soundbank
{
public:
	std::string name;
	uint32_t numSounds;
	ESoundbankType type;
	std::vector<std::string> sounds;

	void Load();

	void Unload();
};