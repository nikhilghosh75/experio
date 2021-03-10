#include "InputMapReader.h"
#include "../Files/LFileOperations.h"

InputMap InputMapReader::ReadInputMap(const std::string & filepath)
{
	if (!LFileOperations::DoesFileHaveExtension(filepath, "pbipmap"))
	{
		// Handle Error here
	}

	std::ifstream inFile(filepath);
	std::string str;

	std::getline(inFile, str);
	if (str != "EXPERIO INPUT MAP")
	{
		// Handle Error here
	}

	InputMap map;
	uint32_t numCategories, numConfigs;
	inFile >> numCategories >> numConfigs;
	map.Resize(numCategories, numConfigs);

	InputCategory& category = map.categories[0];
	InputConfig& config = category.configs[0];
	int currentCategoryIndex = -1;
	int currentConfigIndex = -1;

	while (inFile >> str)
	{
		// INPUT CATEGORY
		if (str == "CATEGORY")
		{
			currentCategoryIndex++;
			category = map.categories[currentCategoryIndex];
			currentConfigIndex = -1;
			inFile >> category.name;
		}
		else if (str == "CONFIG")
		{
			currentConfigIndex++;
			config = map.categories[currentCategoryIndex].configs[currentConfigIndex];
			inFile >> config.name;
			inFile >> str;
			config.inputType = StringToInputType(str);
		}
		else if (str == "ACTION")
		{
			ParseAction(inFile, config);
		}
	}

	return map;
}

EInputType InputMapReader::StringToInputType(const std::string& type)
{
	if (type == "Keyboard")
		return EInputType::Keyboard;
	return EInputType::Gamepad;
}

void InputMapReader::ParseAction(std::ifstream& inFile, InputConfig& config)
{
	std::string actionName;
	std::string actionBinding;
	inFile >> actionName >> actionBinding;


}

void InputMapReader::ParseAxis(std::ifstream& inFile, InputConfig& config)
{
}
