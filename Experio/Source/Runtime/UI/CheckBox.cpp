#include "CheckBox.h"
#include "Canvas.h"
#include "UIQueue.h"
#include "../Input/Input.h"

CheckBox::CheckBox()
{
	this->gameObject = nullptr;
}

CheckBox::CheckBox(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

void CheckBox::Start()
{
	this->shader = ShaderReader::ReadShader(Project::experioResourcesPath + "/Standard/Shaders/ColorPanel.shader");
}

void CheckBox::Update()
{
	UIQueue::AddToQueue(this, gameObject->rectTransform.z, EUIComponentType::Checkbox);
}

void CheckBox::RenderCheckBox()
{
	float canvasWidth = Canvas::GetCanvasWidth();
	float canvasHeight = Canvas::GetCanvasHeight();

	FRect rect = gameObject->GetCanvasSpaceRect();
	rect.min.x /= canvasWidth;
	rect.min.y /= canvasHeight;
	rect.max.x /= canvasWidth;
	rect.max.y /= canvasHeight;

	float cornerPoint = 0;

	FColor color = isOn ? onColor : offColor;

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

void CheckBox::HandleInput()
{
	if (Input::GetMouseButtonDown(EMouseButton::Left))
	{
		isOn = !isOn;
	}
}
