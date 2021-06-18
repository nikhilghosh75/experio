#include "SoundbankReader.h"
#include "../Files/LFileOperations.h"
#include <fstream>

Soundbank SoundbankReader::ReadFromFile(const std::string& filepath)
{
	if (LFileOperations::DoesFileHaveExtension(filepath, "pbbsbnk"))
		return ReadFromBinaryFile(filepath);
	else if (LFileOperations::DoesFileHaveExtension(filepath, "pbsbnk"))
		return ReadFromTextFile(filepath);

	return Soundbank();
}

Soundbank SoundbankReader::ReadFromTextFile(const std::string& filepath)
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

Soundbank SoundbankReader::ReadFromBinaryFile(const std::string& filepath)
{
    return Soundbank();
}
