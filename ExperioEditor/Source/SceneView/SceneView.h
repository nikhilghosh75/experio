#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Rendering/Renderer.h"
#include "Runtime/Rendering/FrameBuffer.h"
#include "Runtime/Math/FVector3.h"
#include "glm/glm.hpp"
#include "ImGuizmo.h"

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

	bool gizmosEnabled;

	Renderer renderer;

	Framebuffer framebuffer;

	ImVec2 lastSize;

	void CreateMenu();

	void ComputeContext();

	FVector2 WorldToPos(glm::vec3 position, glm::mat4 matrix);

	void HandleGizmos();

	static constexpr ImGuizmo::OPERATION SceneEditModeToOperation(ESceneEditMode mode);
public:
	static SceneView* sceneView;

	SceneView();

	virtual void Display() override;
	virtual void HandleInput() override;

	void SetEditMode(ESceneEditMode sceneEditMode);
};