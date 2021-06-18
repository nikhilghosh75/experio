#include "Button.h"
#include "Canvas.h"
#include "UIQueue.h"
#include "../Input/Input.h"
#include "../Rendering/Renderer.h"

Button::Button()
{
	this->gameObject = nullptr;
}

Button::Button(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

void Button::Start()
{
	this->shader = ShaderReader::ReadShader(Project::experioResourcesPath + "/Standard/Shaders/ColorPanel.shader");
}

void Button::Update()
{
	this->isHovered = false;
	UIQueue::AddToQueue(this, gameObject->rectTransform.z, EUIComponentType::Button);
}

void Button::RenderButton()
{
	float canvasWidth = Canvas::GetCanvasWidth();
	float canvasHeight = Canvas::GetCanvasHeight();

	FRect rect = gameObject->GetCanvasSpaceRect();
	rect.min.x /= canvasWidth;
	rect.min.y /= canvasHeight;
	rect.max.x /= canvasWidth;
	rect.max.y /= canvasHeight;

	float cornerPoint = 0;

	FColor color = isPressed ? activeColor : (isHovered ? hoveredColor : defaultColor);

	shader->Bind();
	shader->SetUniformVec4("panelColor", glm::vec4(color.r, color.g, color.b, color.a));
	shader->SetUniformVec2("minCorner", rect.min);
	shader->SetUniformVec2("maxCorner", rect.max);
	shader->SetUniformFloat("cornerPoint", cornerPoint);

	glm::vec2 verticies[6] = {
		rect.GetTopLeft(), rect.GetBottomLeft(), rect.GetTopRight(),
		rect.GetBottomRight(), rect.GetTopRight(), rect.GetBottomLeft()
	};

	VertexBuffer vertexBuffer(verticies, sizeof(verticies));

	VertexArray va;

	VertexBufferLayout vertexLayout;
	vertexLayout.PushFloat(2);

	va.AddBuffer(&vertexBuffer, vertexLayout);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Button::HandleInput()
{
	isHovered = true;
	if (Input::GetMouseButtonDown(EMouseButton::Left))
	{
		isPressed = true;
	}
	else
	{
		isPressed = false;
	}
}
