#include "Billboard.h"
#include "GL/glew.h"
#include <GL/GL.h>
#include "Shader.h"
#include "VertexBuffer.h"
#include "../Core/GWindow.h"
#include "../Core/LWindowOperations.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "../Camera/CameraSystem.h"
#include "Renderer.h"

Billboard::Billboard(GameObject * object)
{
	this->gameObject = object;
}

void Billboard::Start()
{
	this->billboardTexture = new Texture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/HealthBar.bmp");
	this->sizeType = EBillboardSizeType::World;
	this->orientation = EBilboardOrientation::TowardCamera;
	this->billboardSize = FVector2(1.0f, 0.125f);
}

void Billboard::Update()
{
	Renderer::Get()->DrawBillboard(*this, CameraSystem::currentViewMatrix, CameraSystem::currentProjectionMatrix);
}
