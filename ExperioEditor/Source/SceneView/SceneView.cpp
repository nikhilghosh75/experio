#include "SceneView.h"
#include "imgui.h"
#include "../Core/EditorWindow.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "Runtime/Camera/AdditionalCameras.h"
#include "Runtime/Camera/VirtualCamera.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Math/LMath.h"
#include "Runtime/Rendering/Materials/SingleColorMaterial.h"

#define PB_CAMERA_MOVE_SCALE_FACTOR 200.f
#define PB_CAMERA_ROTATE_SCALE_FACTOR 1000.f
#define PB_CAMERA_SCROLL_SCALE_FACTOR 1000.f

#define PB_TRANSLATION_GIZMOS_VERTICIES 912

SceneView* SceneView::sceneView;

static const ImU32 planeColor[3] = { 0x610000AA, 0x6100AA00, 0x61AA0000 };
static const ImU32 selectionColor = 0x8A1080FF;

static const FVector3 directions[3] = { FVector3::right, FVector3::up, FVector3::forward };

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

	this->currentMode = ESceneEditMode::Translate;
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
}

void SceneView::ComputeContext()
{
	this->viewMatrix = VirtualCamera::CalculateViewMatrix(this->cameraPosition, this->cameraRotation);
	this->projectionMatrix = VirtualCamera::CalculateProjectionMatrix(this->fieldOfView, 0.00001f, 1000.f);
	this->modelMatrix = MeshComponent::CalculateModelMatrix(SceneHierarchy::hierarchy->GetSelectedItems()[0]);
	this->MVP = projectionMatrix * viewMatrix * modelMatrix;

	this->modelInverse = glm::inverse(this->modelMatrix);
	this->viewInverse = glm::inverse(this->viewMatrix);
	this->projectionInverse = glm::inverse(this->projectionInverse);

	this->cameraRight = glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
	this->cameraUp = glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
	this->cameraEye = glm::vec3(viewMatrix[0][3], viewMatrix[1][3], viewMatrix[2][3]);
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

	ComputeContext();
	switch (currentMode)
	{
	case ESceneEditMode::Translate:
		HandleTranslation();
		break;
	}
}

void SceneView::HandleTranslation()
{
	glDisable(GL_DEPTH);
	
	// 0 - X, 1 - Y, 2 - Z
	for (int i = 0; i < 3; i++)
	{
		glm::vec3 planeX, planeY, planeAxis;
		ComputeTripodAxis(i, planeAxis, planeX, planeY);


	}

	glEnable(GL_DEPTH);
}

void SceneView::ComputeTripodAxis(int axisIndex, glm::vec3 & dirAxis, glm::vec3 & dirPlaneX, glm::vec3 & dirPlaneY)
{
	dirAxis = directions[axisIndex];
	dirPlaneX = directions[(axisIndex + 1) % 3];
	dirPlaneY = directions[(axisIndex + 2) % 3];

	float lenDir = GetSegmentLengthClipSpace(glm::vec3(0.f, 0.f, 0.f), dirAxis);
	float lenDirMinus = GetSegmentLengthClipSpace(glm::vec3(0.f, 0.f, 0.f), -dirAxis);

	float lenDirPlaneX = GetSegmentLengthClipSpace(glm::vec3(0.f, 0.f, 0.f), dirPlaneX);
	float lenDirMinusPlaneX = GetSegmentLengthClipSpace(glm::vec3(0.f, 0.f, 0.f), -dirPlaneX);

	float lenDirPlaneY = GetSegmentLengthClipSpace(glm::vec3(0.f, 0.f, 0.f), dirPlaneY);
	float lenDirMinusPlaneY = GetSegmentLengthClipSpace(glm::vec3(0.f, 0.f, 0.f), -dirPlaneY);

	float mulAxis = (lenDir < lenDirMinus&& fabsf(lenDir - lenDirMinus) > FLT_EPSILON) ? -1.f : 1.f;
	float mulAxisX = (lenDirPlaneX < lenDirMinusPlaneX&& fabsf(lenDirPlaneX - lenDirMinusPlaneX) > FLT_EPSILON) ? -1.f : 1.f;
	float mulAxisY = (lenDirPlaneY < lenDirMinusPlaneY&& fabsf(lenDirPlaneY - lenDirMinusPlaneY) > FLT_EPSILON) ? -1.f : 1.f;
	dirAxis *= mulAxis;
	dirPlaneX *= mulAxisX;
	dirPlaneY *= mulAxisY;
}

float SceneView::GetSegmentLengthClipSpace(glm::vec3 start, glm::vec3 end)
{
	glm::vec3 startOfSegment = (glm::vec3)(this->MVP * glm::vec4(start, 0.f));
	glm::vec3 endOfSegment = (glm::vec3)(this->MVP * glm::vec4(end, 0.f));

	// If scene gizmos don't work, you know why

	glm::vec3 clipSpaceAxis = endOfSegment - startOfSegment;
	clipSpaceAxis.y /= this->GetAspectRatio();
	float segmentLengthInClipSpace = LMath::Sqrt(clipSpaceAxis.x * clipSpaceAxis.x + clipSpaceAxis.y * clipSpaceAxis.y);
	return segmentLengthInClipSpace;
}

void SceneView::Display()
{
	renderer.MakeCurrent();

	CreateMenu();

	ImVec2 currentSize = ImGui::GetContentRegionAvail();

	AdditionalCameras::CalculateViewMatrix(cameraPosition, cameraRotation);
	AdditionalCameras::CalculateProjectionMatrix(45.f, 0.1f, 1000.f, currentSize.x / currentSize.y);

	FWindowData data = EditorWindow::GetWindowData();
	Framebuffer framebuffer(data.width, data.height);
	framebuffer.Bind();
	Project::componentManager->RenderScene();
	HandleGizmos();
	framebuffer.Unbind();

	ImGui::Image((void*)framebuffer.GetColorAttachment(), currentSize, ImVec2(0, 1), ImVec2(1, 0));
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
