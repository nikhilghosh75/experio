#include "MeshViewer.h"
#include "Runtime/Camera/AdditionalCameras.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Input/Input.h"
#include "Runtime/Rendering/Renderer.h"
#include <sstream>

void MeshViewer::DisplayStats()
{
	if (this->loadedRef.IsNull())
	{
		return;
	}

	std::string meshName = MeshManager::GetNameOfMesh(this->loadedRef);
	ImGui::Text(meshName.c_str());
	
	unsigned int triangleCount = this->loadedRef->GetTriangleCount();
	ImGui::Text(std::to_string(triangleCount).c_str());

	std::stringstream isIndexedStream;
	isIndexedStream << "Is Indexed: ";
	if (this->loadedRef->isIndexed)
	{
		isIndexedStream << "True";
	}
	else
	{
		isIndexedStream << "False";
	}
	ImGui::Text(isIndexedStream.str().c_str());
}

MeshViewer::MeshViewer()
{
	this->category = EEditorModuleCategory::Viewer;
	this->name = "Mesh Viewer";

	this->gameObject.isActive = true;
	this->gameObject.localPosition = FVector3(0, 0, 0);
	this->gameObject.localRotation = FQuaternion(0, 0, 0, 1);
	this->gameObject.localScale = FVector3(1, 1, 1);

	this->cameraPosition = FVector3(4, 3, -3);
	this->cameraRotation = FQuaternion(0.11938, -0.86197, -0.23875, 0.42099);
	this->cameraScrollSpeed = 0.005f;
	this->cameraRotateSpeed = 0.0005f;
}

void MeshViewer::Display()
{
	this->meshComponent.meshData = this->loadedRef;
	this->meshComponent.material = (MeshMaterial*)Project::materialManager->LoadMaterialFromFile("C:/Users/debgh/source/repos/project-bloo/Demo Project/Assets/Materials/SuzanneMat.material");

	if (this->loadedRef.IsNull())
	{
		return;
	}

	Renderer renderer;
	renderer.currentMode = ERenderMode::ToEditorAssetView;
	renderer.MakeCurrent();

	DisplayStats();

	ImVec2 windowSize = ImGui::GetWindowSize();
	ImVec2 currentSize = ImGui::GetWindowSize();
	currentSize = ImVec2(currentSize.x - 12, currentSize.y - 140); // Change Later

	AdditionalCameras::CalculateViewMatrix(cameraPosition, cameraRotation);
	AdditionalCameras::CalculateProjectionMatrix(45.f, 0.1f, 1000.f, currentSize.x / currentSize.y);

	Framebuffer framebuffer(windowSize.x, windowSize.y);
	framebuffer.Bind();
	renderer.DrawMesh(this->meshComponent);
	framebuffer.Unbind();

	ImGui::Image((void*)framebuffer.GetColorAttachment(), currentSize, ImVec2(0, 1), ImVec2(1, 0));
}

void MeshViewer::HandleInput()
{
	this->cameraPosition += this->cameraRotation.Rotate(FVector3(Input::GetMouseScrollDelta(), 0, 0));

	FVector2 mouseDelta = Input::GetMouseDelta();
	if (mouseDelta.SqrMagnitude() > 0 && Input::GetMouseButton(EMouseButton::Middle))
	{
		FVector3 difference = this->cameraPosition;
		FQuaternion aroundY = FQuaternion(FVector3(0, 1, 0), mouseDelta.x * this->cameraRotateSpeed);
		difference = aroundY.Rotate(difference);
		FQuaternion aroundX = FQuaternion(FVector3(1, 0, 0), mouseDelta.y * this->cameraRotateSpeed);
		difference = aroundX.Rotate(difference);
		this->cameraPosition = difference;
		this->cameraRotation = glm::lookAt((glm::vec3)this->cameraPosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}
}
