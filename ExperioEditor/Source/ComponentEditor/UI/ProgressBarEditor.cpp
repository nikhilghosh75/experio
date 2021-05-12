#include "ProgressBarEditor.h"
#include "Runtime/Rendering/ImGui/LImGui.h"

void ProgressBarEditor::Display(Component* component)
{
	ProgressBar* progressBar = (ProgressBar*)component;

	float valueSpeed = (progressBar->maxValue - progressBar->minValue) / 100;

	ImGui::DragFloat("Min Value", &progressBar->minValue, 1);
	ImGui::DragFloat("Max Value", &progressBar->maxValue, 1);
	ImGui::DragFloat("Value", &progressBar->value, valueSpeed, 
		progressBar->minValue, progressBar->maxValue);
	ImGui::ColorEdit4("Background Color", (float*)&progressBar->backgroundColor, ImGuiColorEditFlags_Float);
	ImGui::ColorEdit4("Bar Color", (float*)&progressBar->barColor, ImGuiColorEditFlags_Float);
	LImGui::DisplayEnum<EProgressBarMode>(progressBar->mode, "Mode");
}
