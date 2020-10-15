#include "SceneView.h"
#include "imgui.h"
#include "../Core/EditorWindow.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "Runtime/Camera/AdditionalCameras.h"
#include "Runtime/Math/LMath.h"
#include "Runtime/Rendering/Materials/SingleColorMaterial.h"

#define PB_CAMERA_MOVE_SCALE_FACTOR 200.f
#define PB_CAMERA_ROTATE_SCALE_FACTOR 1000.f
#define PB_CAMERA_SCROLL_SCALE_FACTOR 1000.f

#define PB_TRANSLATION_GIZMOS_VERTICIES 912

SingleColorMaterial* singleColorMaterial;
float translationColors[4 * PB_TRANSLATION_GIZMOS_VERTICIES];

SceneView::SceneView()
{
	this->name = "Scene View";
	this->category = EEditorModuleCategory::Core;

	this->renderer.currentMode = ERenderMode::ToEditorSceneView;
	this->cameraPosition = FVector3(4, 3, -3);
	this->cameraRotation = FQuaternion(0.11938, -0.86197, -0.23875, 0.42099);
	this->cameraCenter = FVector3();
	this->cameraMoveSpeed = 0.01f;
	this->cameraScrollSpeed = 0.005f;
	this->cameraRotateSpeed = 0.0005f;
	this->currentMode = ESceneEditMode::Translate;

	this->translationMesh = MeshReader::ReadFile("C:/Users/debgh/source/repos/project-bloo/ExperioEditor/Resources/Meshes/translationGizmo.obj");
	
	if (singleColorMaterial == nullptr)
	{
		singleColorMaterial = new SingleColorMaterial();
		singleColorMaterial->SetShader(
			"C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Shaders/SingleColorVertex.shader",
			"C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Shaders/SingleColorFragment.shader"
		);

		for (int i = 0; i < PB_TRANSLATION_GIZMOS_VERTICIES; i++)
		{
			// FIGURE THIS OUT LATER
			translationColors[i * 4] = (float)i / PB_TRANSLATION_GIZMOS_VERTICIES;
			translationColors[i * 4 + 1] = (float)i / PB_TRANSLATION_GIZMOS_VERTICIES;
			translationColors[i * 4 + 2] = 0.0f;
			translationColors[i * 4 + 3] = 1.0f;
		}

	}
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

void SceneView::HandleGizmos()
{
	return;
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
	
	GameObject tempObject = GameObject("Temp");
	std::vector<GameObject> selectedObjects = SceneHierarchy::hierarchy->GetSelectedItems();
	VertexBuffer colorBuffer = VertexBuffer(translationColors, 4 * PB_TRANSLATION_GIZMOS_VERTICIES);
	singleColorMaterial->colorBuffer = &colorBuffer;

	for (int i = 0; i < selectedObjects.size(); i++)
	{
		tempObject.localPosition = selectedObjects[i].localPosition;
		tempObject.localScale = FVector3(0.9, 0.9, 0.9);
		MeshComponent meshComponent(&tempObject);
		meshComponent.meshData = translationMesh;
		meshComponent.material = singleColorMaterial;
		meshComponent.RecalculateModelMatrix();
		renderer.DrawMesh(meshComponent);
	}

	glEnable(GL_DEPTH);
}

void SceneView::Display()
{
	renderer.MakeCurrent();

	ImVec2 currentSize = ImGui::GetWindowSize();
	currentSize = ImVec2(currentSize.x - 12, currentSize.y - 130); // Change Later

	AdditionalCameras::CalculateViewMatrix(cameraPosition, cameraRotation);
	AdditionalCameras::CalculateProjectionMatrix(45.f, 0.1f, 1000.f, currentSize.x / currentSize.y);

	CreateMenu();

	FWindowData data = EditorWindow::GetWindowData();
	Framebuffer framebuffer(data.width, data.height);
	framebuffer.Bind();
	Project::componentManager->Update();
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
}
