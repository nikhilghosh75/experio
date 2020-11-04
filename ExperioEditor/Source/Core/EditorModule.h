#pragma once
#include <string>
#include "Runtime/Math/FRect.h"

enum class EEditorModuleCategory : uint8_t
{
	Core, // Hierarchy, Scene View, etc.
	Profiling, // Scene and Frame Profiler
	Experimental, // For things that are experimental
	Viewer, // For asset viewer
	Custom
};

class EditorModule
{
protected:
	FRect GetWindowRect(); // Only call this between ImGui::Begin and ImGui::End
public:
	std::string name;
	EEditorModuleCategory category;
	
	virtual void Display() {};

	virtual void HandleInput() {};

	// Add EditorInput
};