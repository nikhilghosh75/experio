#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Rendering/Renderer.h"
#include "Runtime/Files/Mesh/MeshReader.h"
#include "Runtime/Rendering/Managers/MeshManager.h"
#include "Runtime/Math/FVector3.h"

enum class ESceneEditMode
{
	Translate,
	Rotate,
	Scale
};

class SceneView : public EditorModule
{
	FVector3 cameraPosition;
	FQuaternion cameraRotation;

	FVector3 cameraCenter;

	ESceneEditMode currentMode;

	float cameraMoveSpeed;
	float cameraScrollSpeed;
	float cameraRotateSpeed;

	Renderer renderer;

	MeshRef translationMesh;
	MeshRef rotationMesh;
	MeshRef scaleMesh;

	void CreateMenu();

	void HandleGizmos();
	void HandleTranslation();
public:
	SceneView();

	virtual void Display() override;
	virtual void HandleInput() override;
};