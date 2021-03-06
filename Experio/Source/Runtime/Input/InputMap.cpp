#include "InputMap.h"

InputAction::InputAction()
{
	name = "";
	code.keycode = EKeyCode::None;
}

InputAction::InputAction(const std::string& str)
{
	name = str;
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

const std::string& InputMap::GetCurrentCategory() const
{
	return categories[currentCategory].name;
}
