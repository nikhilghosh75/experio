#pragma once
#include <string>

enum class EComponentStage : uint8_t
{
	PreCamera,
	Camera,
	PostCamera,
	PreRendering,
	Rendering,
	PrePostprocessing,
	PreUI,
	UI,
	PostUI
};

struct FComponentInfo
{
	std::string name;
	std::string filepath;
	std::string category;

	EComponentStage stage;

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

	bool operator<(const FComponentInfo& info1) const
	{
		return (uint8_t)this->stage < (uint8_t)info1.stage;
	}
};