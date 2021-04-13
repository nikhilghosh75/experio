#pragma once
#include "InputCodes.h"
#include "../Containers/TStackArray.h"
#include <string>
#include <vector>

class InputAction
{
public:
	std::string name;
	InputCode code;

	InputAction();
	InputAction(const std::string& str);
	InputAction(const std::string& str, InputCode code);
	InputAction(const std::string& str, EKeyCode keyCode);
	InputAction(const std::string& str, EGamepadButton gamepadButton);
};

class InputAxisPoint
{
public:
	float value;
	InputCode code;
	
	InputAxisPoint() = default;
	InputAxisPoint(float value, InputCode code);
};

class InputAxis
{
public:
	std::string name;
	TStackArray<InputAxisPoint, 4> axisPoints;

	InputAxis() = default;
	InputAxis(const std::string& str);
};

class InputConfig
{
public:
	InputConfig() = default;
	InputConfig(const std::string& name);

	std::string name;

	std::vector<InputAction> actions;
	
	std::vector<InputAxis> axes;

	EInputType inputType;
};

class InputCategory
{
public:
	InputCategory() = default;
	InputCategory(const std::string& name);

	std::vector<InputConfig> configs;

	std::string name;
};

class InputMap
{
	friend class InputMapReader;
	friend class InputMapViewer;

	void Resize(uint32_t numCategories, uint32_t numConfigs);

	std::vector<InputCategory> categories;

	uint32_t currentCategory;
public:
	void EnableCategory(uint32_t currentCategory);
	void EnableCategory(const std::string& categoryName);

	size_t NumCategories() const;
	size_t NumConfigs() const;

	const std::string& GetCurrentCategory() const;

	bool IsEmpty() const;
};