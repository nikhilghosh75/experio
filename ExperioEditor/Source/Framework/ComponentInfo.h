#pragma once
#include <string>

struct FComponentInfo
{
	std::string name;
	std::string filepath;

	bool isStandaloneComponent;
	bool isDefaultComponent;

	FComponentInfo() = default;

	FComponentInfo(const std::string& name, bool isStandaloneComponent)
	{
		this->name = name;
		this->isStandaloneComponent = isStandaloneComponent;
		this->isDefaultComponent = false;
	}

	FComponentInfo(const std::string& name, bool isStandaloneComponent, bool isDefaultComponent)
	{
		this->name = name;
		this->isStandaloneComponent = isStandaloneComponent;
		this->isDefaultComponent = isDefaultComponent;
	}

	FComponentInfo(const std::string& name, const std::string& filename, bool isStandaloneComponent, bool isDefaultComponent)
	{
		this->name = name;
		this->filepath = filename;
		this->isStandaloneComponent = isStandaloneComponent;
		this->isDefaultComponent = isDefaultComponent;
	}
};