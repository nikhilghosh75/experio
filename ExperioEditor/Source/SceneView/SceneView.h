#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Rendering/Renderer.h"
#include "Runtime/Math/FVector3.h"

class SceneView : public EditorModule
{
	FVector3 cameraPosition;
	FQuaternion cameraRotation;

	FVector3 cameraCenter;

	float cameraMoveSpeed;
	float cameraScrollSpeed;
	float cameraRotateSpeed;

	Renderer renderer;

	void CreateMenu();
public:
	SceneView();

	virtual void Display() override;
	virtual void HandleInput() override;
};