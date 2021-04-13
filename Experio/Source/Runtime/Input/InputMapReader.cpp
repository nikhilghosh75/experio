#include "InputMapReader.h"
#include "../Files/LFileOperations.h"
#include "../../ThirdParty/Magic Enum/magic_enum.hpp"

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

	// InputCategory& category = map.categories[0];
	// InputConfig& config = category.configs[0];
	int currentCategoryIndex = -1;
	int currentConfigIndex = -1;

	while (inFile >> str)
	{
		// INPUT CATEGORY
		if (str == "CATEGORY")
		{
			currentCategoryIndex++;
			currentConfigIndex = -1;
			inFile >> map.categories[currentCategoryIndex].name;
		}
		else if (str == "CONFIG")
		{
			currentConfigIndex++;
			inFile >> map.categories[currentCategoryIndex].configs[currentConfigIndex].name;
			inFile >> str;
			map.categories[currentCategoryIndex].configs[currentConfigIndex].inputType = StringToInputType(str);
		}
		else if (str == "ACTION")
		{
			ParseAction(inFile, map.categories[currentCategoryIndex].configs[currentConfigIndex]);
		}
		else if (str == "AXIS")
		{
			ParseAxis(inFile, map.categories[currentCategoryIndex].configs[currentConfigIndex]);
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

InputCode InputMapReader::StringToInputCode(const std::string& str, EInputType inputType)
{
	InputCode code;
	switch (inputType)
	{
	case EInputType::Keyboard:
		code.keycode = magic_enum::enum_cast<EKeyCode>(str).value_or(EKeyCode::None);
		break;
	case EInputType::Gamepad:
		code.gamepadButton = magic_enum::enum_cast<EGamepadButton>(str).value_or(EGamepadButton::None);
		break;
	}
	return code;
}

void InputMapReader::ParseAction(std::ifstream& inFile, InputConfig& config)
{
	std::string actionName;
	std::string actionBinding;
	inFile >> actionName >> actionBinding;

	InputCode actionCode = StringToInputCode(actionBinding, config.inputType);

	config.actions.emplace_back(actionName, actionCode);
}

void InputMapReader::ParseAxis(std::ifstream& inFile, InputConfig& config)
{
	std::string axisName;
	int numAxisPoints;
	inFile >> axisName >> numAxisPoints;

	InputAxis& axis = config.axes.emplace_back(axisName);
	for (int i = 0; i < numAxisPoints; i++)
	{
		std::string pointBinding;
		float pointValue;
		inFile >> pointBinding >> pointValue;
		
		InputCode pointCode = StringToInputCode(pointBinding, config.inputType);
		InputAxisPoint point(pointValue, pointCode);
		axis.axisPoints.Append(point);
	}
}
