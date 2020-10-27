#include "MeshComponentEditor.h"
#include "imgui.h"
#include "Runtime/Rendering/ImGui/LImGui.h"

void MeshEditor::Display(Component * component)
{
	MeshComponent* meshComponent = (MeshComponent*)component;

	ImGui::Text("Material: Standard");
	LImGui::DisplayMeshAsset(meshComponent->meshData, "Mesh");
	LImGui::DisplayBool(meshComponent->isVisible, "Is Visible");
}