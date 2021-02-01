#pragma once
#include <string>
#include "Runtime/Math/FRect.h"

enum class EEditorModuleCategory : uint8_t
{
	Core, // Hierarchy, Scene View, etc.
	Profiling, // Scene and Frame Profiler
	Experimental, // For things that are experimental
	Viewer, // For asset viewer
	Testing, // For testing
	Custom
};

class EditorModule
{
	bool isDisplayed = true;
protected:
	FRect GetWindowRect(); // Only call this between ImGui::Begin and ImGui::End
	FVector2 GetWindowSize(); // Only call this between ImGui::Begin and ImGui::End
	FVector2 GetWindowPosition(); // Only call this between ImGui::Begin and ImGui::End

	float GetAspectRatio(); // Only call this between ImGui::Begin and ImGui::End
public:
	std::string name;
	EEditorModuleCategory category;
	
	virtual void Display() {};

	virtual void HandleInput() {};

	bool* GetIsDisplayed() { return &isDisplayed; }
	// Add EditorInput
};