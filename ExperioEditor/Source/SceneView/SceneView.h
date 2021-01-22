#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Rendering/Renderer.h"
#include "Runtime/Files/Mesh/MeshReader.h"
#include "Runtime/Rendering/Managers/MeshManager.h"
#include "Runtime/Math/FVector3.h"
#include "glm/glm.hpp"

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
	float fieldOfView;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
	glm::mat4 modelInverse;
	glm::mat4 viewInverse;
	glm::mat4 projectionInverse;
	glm::mat4 MVP;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 cameraEye;

	Renderer renderer;

	void CreateMenu();

	void ComputeContext();

	FVector2 WorldToPos(glm::vec3 position, glm::mat4 matrix);

	void HandleGizmos();

	// Translation Gizmo
	void HandleTranslation();

	void ComputeTripodAxis(int axisIndex, glm::vec3& dirAxis, glm::vec3& dirPlaneX, glm::vec3& dirPlaneY);
	
	float GetSegmentLengthClipSpace(glm::vec3 start, glm::vec3 end);

	// Rotation Gizmo

	// Scale Gizmo
public:
	static SceneView* sceneView;

	SceneView();

	virtual void Display() override;
	virtual void HandleInput() override;

	void SetEditMode(ESceneEditMode sceneEditMode);
};