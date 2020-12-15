#pragma once
#include <string>
#include <vector>

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
};