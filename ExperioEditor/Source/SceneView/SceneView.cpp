#include "SceneView.h"
#include "imgui.h"
#include "../Core/EditorWindow.h"
#include "Runtime/Camera/AdditionalCameras.h"

SceneView::SceneView()
{
	this->category = EEditorModuleCategory::Core;
	renderer.currentMode = ERenderMode::ToEditorSceneView;
}

void SceneView::Display()
{
	renderer.MakeCurrent();

	ImVec2 currentSize = ImGui::GetWindowSize();
	currentSize = ImVec2(currentSize.x - 12, currentSize.y - 35); // Change Later

	AdditionalCameras::CalculateViewMatrix(FVector3(4, 3, -3), FQuaternion(0.11938, -0.86197, -0.23875, 0.42099));
	AdditionalCameras::CalculateProjectionMatrix(45.f, 0.1f, 1000.f, currentSize.x / currentSize.y);

	FWindowData data = EditorWindow::GetWindowData();
	Framebuffer framebuffer(data.width, data.height);
	framebuffer.Bind();
	Project::componentManager->Update();
	framebuffer.Unbind();
	ImGui::Image((void*)framebuffer.GetColorAttachment(), currentSize, ImVec2(0, 1), ImVec2(1, 0));
}
