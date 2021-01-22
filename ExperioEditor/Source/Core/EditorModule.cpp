#include "EditorModule.h"

FRect EditorModule::GetWindowRect()
{
	FVector2 position = ImGui::GetWindowPos();
	FVector2 size = ImGui::GetWindowSize();
	return FRect(position, position + size);
}

FVector2 EditorModule::GetWindowSize()
{
	return ImGui::GetWindowSize();
}

FVector2 EditorModule::GetWindowPosition()
{
	return ImGui::GetWindowSize();
}

float EditorModule::GetAspectRatio()
{
	FVector2 size = ImGui::GetWindowSize();
	return size.x / size.y;
}
