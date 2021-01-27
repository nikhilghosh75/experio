#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Rendering/Managers/MeshManager.h"
#include "Runtime/Rendering/Components/MeshComponent.h"

class MeshViewer : public EditorModule
{
	MeshComponent meshComponent;
	GameObject gameObject;

	FVector3 cameraPosition;
	FQuaternion cameraRotation;

	float cameraScrollSpeed;
	float cameraRotateSpeed;

	void DisplayStats();

	std::string filepath;
public:
	MeshRef loadedRef;

	MeshViewer();

	virtual void Display() override;
	virtual void HandleInput() override;
};