#pragma once
#include "InputCodes.h"
#include <string>
#include <vector>

class InputAction
{
	std::string name;
	InputCode code;

	InputAction();
	InputAction(const std::string& str);
	InputAction(const std::string& str, EKeyCode keyCode);
	InputAction(const std::string& str, EGamepadButton gamepadButton);
};

class InputConfig
{
public:
	std::string name;

	EInputType inputType;
};

class InputCategory
{
public:
	std::vector<InputConfig> configs;

	std::string name;
};

class InputMap
{
	friend class InputMapReader;

	void Resize(uint32_t numCategories, uint32_t numConfigs);

	std::vector<InputCategory> categories;

	uint32_t currentCategory;
public:
	void EnableCategory(uint32_t currentCategory);
	void EnableCategory(const std::string& categoryName);

	const std::string& GetCurrentCategory() const;
};