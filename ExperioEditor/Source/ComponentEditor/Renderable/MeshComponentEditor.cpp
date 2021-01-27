#include "MeshComponentEditor.h"
#include "imgui.h"
#include "../../AssetViewers/MeshViewer.h"
#include "../../Core/EditorApplication.h"
#include "Runtime/Rendering/ImGui/LImGui.h"

void MeshEditor::Display(Component * component)
{
	MeshComponent* meshComponent = (MeshComponent*)component;

	ImGui::Text("Material: Standard");
	LImGui::DisplayMeshAsset(meshComponent->meshData, "Mesh");
	LImGui::DisplayBool(meshComponent->isVisible, "Is Visible");
}

void MeshEditor::ContextMenu(Component * mesh)
{
	MeshComponent* meshComponent = (MeshComponent*)mesh;

	if (ImGui::Selectable("View Mesh"))
	{
		MeshViewer* viewer = (MeshViewer*)EditorApplication::AddModule(new MeshViewer());
		viewer->loadedRef = meshComponent->meshData;
	}
}
