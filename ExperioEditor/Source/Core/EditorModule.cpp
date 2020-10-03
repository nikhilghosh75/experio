#include "EditorModule.h"

FRect EditorModule::GetWindowRect()
{
	FVector2 position = ImGui::GetWindowPos();
	FVector2 size = ImGui::GetWindowSize();
	return FRect(position, position + size);
}
