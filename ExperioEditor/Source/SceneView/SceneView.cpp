#include "SceneView.h"
#include "imgui.h"
#include "../Core/EditorWindow.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "Runtime/Camera/AdditionalCameras.h"
#include "Runtime/Camera/VirtualCamera.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Math/ColorPalette.h"
#include "Runtime/Math/LMath.h"
#include "Runtime/Rendering/Materials/SingleColorMaterial.h"

#define PB_CAMERA_MOVE_SCALE_FACTOR 200.f
#define PB_CAMERA_ROTATE_SCALE_FACTOR 1000.f
#define PB_CAMERA_SCROLL_SCALE_FACTOR 1000.f

SceneView* SceneView::sceneView;

SceneView::SceneView()
{
	sceneView = this;

	this->name = "Scene View";
	this->category = EEditorModuleCategory::Core;

	this->renderer.currentMode = ERenderMode::ToEditorSceneView;

	this->cameraPosition = FVector3(4, 3, -3);
	this->cameraRotation = FQuaternion(0.11938, -0.86197, -0.23875, 0.42099);
	this->cameraCenter = FVector3();

	this->cameraMoveSpeed = 0.01f;
	this->cameraScrollSpeed = 0.005f;
	this->cameraRotateSpeed = 0.0005f;
	this->fieldOfView = 45.f;

	this->gizmosEnabled = true;
	this->currentMode = ESceneEditMode::Scale;

	FWindowData data = EditorWindow::GetWindowData();
	this->framebuffer = Framebuffer(data.width, data.height);
	this->lastSize = ImVec2(0, 0);
}

void SceneView::CreateMenu()
{
	float displayCameraMoveSpeed = PB_CAMERA_MOVE_SCALE_FACTOR * this->cameraMoveSpeed;
	float displayCameraRotateSpeed = PB_CAMERA_ROTATE_SCALE_FACTOR * this->cameraRotateSpeed;
	float displayCameraScrollSpeed = PB_CAMERA_SCROLL_SCALE_FACTOR * this->cameraScrollSpeed;

	if (ImGui::RadioButton("Translate", currentMode == ESceneEditMode::Translate))
		currentMode = ESceneEditMode::Translate;
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", currentMode == ESceneEditMode::Rotate))
		currentMode = ESceneEditMode::Rotate;
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", currentMode == ESceneEditMode::Scale))
		currentMode = ESceneEditMode::Scale;

	ImGui::SliderFloat("Move Speed", &displayCameraMoveSpeed, 1, 10);
	ImGui::SliderFloat("Scroll Speed", &displayCameraScrollSpeed, 1, 10);
	ImGui::SliderFloat("Rotate Speed", &displayCameraRotateSpeed, 1, 10);

	this->cameraMoveSpeed = displayCameraMoveSpeed / PB_CAMERA_MOVE_SCALE_FACTOR;
	this->cameraRotateSpeed = displayCameraRotateSpeed / PB_CAMERA_ROTATE_SCALE_FACTOR;
	this->cameraScrollSpeed = displayCameraScrollSpeed / PB_CAMERA_SCROLL_SCALE_FACTOR;

	ImGui::Checkbox("Gizmos Enabled", &this->gizmosEnabled);
}

void SceneView::ComputeContext()
{
	this->viewMatrix = VirtualCamera::CalculateViewMatrix(this->cameraPosition, this->cameraRotation);
	this->projectionMatrix = VirtualCamera::CalculateProjectionMatrix(this->fieldOfView, 0.00001f, 1000.f);
	this->modelMatrix = MeshComponent::CalculateModelMatrix(SceneHierarchy::hierarchy->GetSelectedItems()[0]);
}

FVector2 SceneView::WorldToPos(glm::vec3 position, glm::mat4 matrix)
{
	FVector2 size = this->GetWindowSize();
	FVector2 windowPosition = this->GetWindowPosition();

	glm::vec4 transPosition = matrix * glm::vec4(position, 0);
	transPosition *= 0.5f / transPosition.w;
	transPosition += glm::vec4(0.5f, 0.5f, 0.f, 0.f);
	transPosition.y = 1.f - transPosition.y;
	transPosition.x *= size.x;
	transPosition.y *= size.y;
	transPosition.x += windowPosition.x;
	transPosition.y += windowPosition.y;
	return FVector2(transPosition.x, transPosition.y);
}

void SceneView::HandleGizmos()
{
	if (SceneHierarchy::hierarchy->GetSelectedItems().size() == 0) return;

	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

	ComputeContext();
	ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), SceneEditModeToOperation(currentMode),
		ImGuizmo::MODE::LOCAL, glm::value_ptr(modelMatrix));

	GameObject* object = Scene::FindGameObjectFromId(SceneHierarchy::hierarchy->GetSelectedItems()[0].id);
	object->SetTransform(modelMatrix);
}

constexpr ImGuizmo::OPERATION SceneView::SceneEditModeToOperation(ESceneEditMode mode)
{
	switch (mode)
	{
	case ESceneEditMode::Translate: return ImGuizmo::OPERATION::TRANSLATE;
	case ESceneEditMode::Rotate: return ImGuizmo::OPERATION::ROTATE;
	case ESceneEditMode::Scale: return ImGuizmo::OPERATION::SCALE;
	}
	return ImGuizmo::OPERATION();
}

void SceneView::Display()
{
	renderer.MakeCurrent();
	renderer.SetCull(true);

	CreateMenu();

	ImVec2 currentSize = ImGui::GetContentRegionAvail();

	AdditionalCameras::CalculateViewMatrix(cameraPosition, cameraRotation);
	AdditionalCameras::CalculateProjectionMatrix(45.f, 0.1f, 1000.f, currentSize.x / currentSize.y);
	
	if (!LMath::ApproxEquals(currentSize.x, lastSize.x, 2) || !LMath::ApproxEquals(currentSize.y, lastSize.y, 2))
	{
		framebuffer.SetSpec((unsigned int)currentSize.x, (unsigned int)currentSize.y);
	}
	framebuffer.Bind();
	renderer.SetViewport(0, 0, currentSize.x, currentSize.y);
	renderer.ClearColor(ColorPalette::Black);
	renderer.Clear();
	Project::componentManager->RenderScene();
	framebuffer.Unbind();

	ImGui::Image((void*)framebuffer.GetColorAttachment(), currentSize, ImVec2(0, 1), ImVec2(1, 0));

	lastSize = currentSize;
	
	if(gizmosEnabled)
		HandleGizmos();
}

void SceneView::HandleInput()
{
	if (Input::GetKey(EKeyCode::W))
	{
		this->cameraPosition += this->cameraRotation.Rotate(FVector3(0, this->cameraMoveSpeed, 0));
	}
	else if (Input::GetKey(EKeyCode::S))
	{
		this->cameraPosition += this->cameraRotation.Rotate(FVector3(0, -this->cameraMoveSpeed, 0));
	}

	if (Input::GetKey(EKeyCode::D))
	{
		this->cameraPosition += this->cameraRotation.Rotate(FVector3(0, 0, this->cameraMoveSpeed));
	}
	else if (Input::GetKey(EKeyCode::A))
	{
		this->cameraPosition += this->cameraRotation.Rotate(FVector3(0, 0, -this->cameraMoveSpeed));
	}

	this->cameraPosition += this->cameraRotation.Rotate(FVector3(Input::GetMouseScrollDelta(), 0, 0));

	FVector2 mouseDelta = Input::GetMouseDelta();
	if (mouseDelta.SqrMagnitude() > 0 && Input::GetMouseButton(EMouseButton::Middle))
	{
		FVector3 difference = this->cameraPosition - this->cameraCenter;
		FQuaternion aroundY = FQuaternion(FVector3(0, 1, 0), mouseDelta.x * this->cameraRotateSpeed);
		difference = aroundY.Rotate(difference);
		FQuaternion aroundX = FQuaternion(FVector3(1, 0, 0), mouseDelta.y * this->cameraRotateSpeed);
		difference = aroundX.Rotate(difference);
		this->cameraPosition = this->cameraCenter + difference;
		this->cameraRotation = glm::lookAt((glm::vec3)this->cameraPosition, (glm::vec3)this->cameraCenter, glm::vec3(0, 1, 0));
	}

	if (Input::GetKeyDown(EKeyCode::T))
		SetEditMode(ESceneEditMode::Translate);
	else if (Input::GetKeyDown(EKeyCode::Y))
		SetEditMode(ESceneEditMode::Rotate);
	else if (Input::GetKeyDown(EKeyCode::U))
		SetEditMode(ESceneEditMode::Scale);
}

void SceneView::SetEditMode(ESceneEditMode sceneEditMode)
{
	currentMode = sceneEditMode;
}
