#include "InputMap.h"

InputAction::InputAction()
{
	name = "";
	code.keycode = EKeyCode::None;
}

InputAction::InputAction(const std::string& str)
{
	name = str;
	code.keycode = EKeyCode::None;
}

InputAction::InputAction(const std::string& str, InputCode newCode)
{
	name = str;
	code = newCode;
}

InputAction::InputAction(const std::string& str, EKeyCode keyCode)
{
	name = str;
	code.keycode = keyCode;
}

InputAction::InputAction(const std::string& str, EGamepadButton gamepadButton)
{
	name = str;
	code.gamepadButton = gamepadButton;
}

InputAxisPoint::InputAxisPoint(float value, InputCode code)
{
	this->value = value;
	this->code = code;
}

InputAxis::InputAxis(const std::string& str)
{
	this->name = str;
}

InputConfig::InputConfig(const std::string& name)
{
	this->name = name;
}

InputCategory::InputCategory(const std::string& name)
{
	this->name = name;
}

void InputMap::Resize(uint32_t numCategories, uint32_t numConfigs)
{
	this->categories.resize(numCategories);
	for (uint32_t i = 0; i < numCategories; i++)
	{
		this->categories[i].configs.resize(numConfigs);
	}
}

void InputMap::EnableCategory(uint32_t newCategory)
{
	this->currentCategory = newCategory;
}

void InputMap::EnableCategory(const std::string& categoryName)
{
	for (size_t i = 0; i < categories.size(); i++)
	{
		if (categories[i].name == categoryName)
		{
			this->currentCategory = i;
			return;
		}
	}
}

size_t InputMap::NumCategories() const
{
	return categories.size();
}

size_t InputMap::NumConfigs() const
{
	size_t numConfigs = 0;
	for (size_t i = 0; i < categories.size(); i++)
	{
		size_t currentConfigs = categories[i].configs.size();
		numConfigs = currentConfigs > numConfigs ? currentConfigs : numConfigs;
	}
	return numConfigs;
}

const std::string& InputMap::GetCurrentCategory() const
{
	return categories[currentCategory].name;
}

bool InputMap::IsEmpty() const
{
	return categories.size() == 0;
}
