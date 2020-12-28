#include "Soundbank.h"
#include <fstream>
#include "../Debug/Debug.h"

void Soundbank::Load()
{
	Debug::LogError("Load Soundbank function has not been implemented");
}

Soundbank Soundbank::ReadFromFile(const std::string& filepath)
{
	Soundbank soundbank;

	std::ifstream inFile(filepath);
	std::string str;

	inFile >> str >> soundbank.name;
	inFile >> str >> soundbank.numSounds;
	inFile >> str >> str;

	if (str == "Folder")
		soundbank.type = ESoundbankType::Folder;
	else
		soundbank.type = ESoundbankType::Audio;

	for (size_t i = 0; i < soundbank.numSounds; i++)
	{
		inFile >> str;
		soundbank.sounds.push_back(str);
	}

	return soundbank;
}
