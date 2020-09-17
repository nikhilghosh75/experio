#pragma once
#include <string>

enum class EEditorModuleCategory : uint8_t
{
	Core, // Hierarchy, Scene View, etc.
	Profiling, // Scene Profiler
	Experimental, // For things that are experimental
	Custom
};

class EditorModule
{
public:
	std::string name;
	EEditorModuleCategory category;
	
	virtual void Display() {};

	// Add EditorInput
};