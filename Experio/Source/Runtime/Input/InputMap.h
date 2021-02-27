#pragma once
#include <string>
#include <vector>

// Add more categories for input later
enum class EInputType
{
	Keyboard,
	Gamepad
};

class InputAction
{

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