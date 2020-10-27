#include "VirtualCameraEditor.h"
#include "Runtime/Rendering/ImGui/LImGui.h"

void VirtualCameraEditor::Display(Component * virtualCameraComponent)
{
	VirtualCamera* virtualCamera = (VirtualCamera*)virtualCameraComponent;

	ImGui::DragFloat("Priority", &virtualCamera->priority, 0.1f, 0.f, 1000.f);
	ImGui::DragFloat("Field of View", &virtualCamera->fieldOfView, 0.1f, 0.f, 180.f);
	ImGui::DragFloat("Near Clip Plane", &virtualCamera->nearClipPlane, 0.0001f, 0.f, 1.f);
	ImGui::DragFloat("Far Clip Plane", &virtualCamera->farClipPlane, 1.f, 100.f, 1000000.f);
}
