#include "Billboard.h"
#include "GL/glew.h"
#include <GL/GL.h>
#include "../Shaders/Shader.h"
#include "../VertexBuffer.h"
#include "../../Core/Window.h"
#include "../../Core/LWindowOperations.h"
#include "../VertexBufferLayout.h"
#include "../VertexArray.h"
#include "../../Camera/CameraSystem.h"
#include "../Renderer.h"

Billboard::Billboard(GameObject * object)
{
	this->gameObject = object;
}

void Billboard::Start()
{
	// this->sizeType = EBillboardSizeType::World;
	// this->orientation = EBilboardOrientation::TowardCamera;
	// this->billboardSize = FVector2(1.0f, 0.125f);
}

void Billboard::Update()
{
	Renderer::Get()->DrawBillboard(*this);
}
