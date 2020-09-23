#include "ValueLoader.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Debug/Debug.h"
#include <fstream>

using namespace Experio;

void ValueLoader::LoadValues(std::string fileName)
{
	if (!LFileOperations::DoesFileHaveExtension(fileName, "pbvalues"))
	{
		Debug::LogError("Loaded Values is not a .pbvalues");
		return;
	}

	std::ifstream valueFile(fileName);
	if (valueFile.fail())
	{
		Debug::LogError("File " + fileName + " could not be opened");
		return;
	}

	char word[256];

	// Check first line
	valueFile.getline(word, 256);
	if (strcmp(word, "EXPERIO PROJECT VALUES"))
	{
		Debug::LogError("File " + fileName + " is improperly formatted");
		return;
	}

	// Project Name Checking
	valueFile >> word >> word;
	valueFile.getline(word, 256);

	// Add Project Name Checking

	// Check Version
	valueFile >> word;
	valueFile.getline(word, 256);

	// Figure out current type
	EValueType currentType;
	valueFile >> word;
	currentType = GetTypeFromString(word);

	int valueNum;
	valueFile >> valueNum;

	for (int i = 0; i < valueNum; i++)
	{
		int index;
		std::string name;
		valueFile >> index >> name;
		
		AddValue(FValue(index, name), currentType);
	}
}

EValueType ValueLoader::GetTypeFromString(const char * type)
{
	if (strcmp(type, "Tags") == 0)
	{
		return EValueType::Tag;
	}
	if (strcmp(type, "Layers") == 0)
	{
		return EValueType::Layer;
	}
	return EValueType::Unknown;
}
