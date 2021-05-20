#include "Panel.h"
#include "../Core/LWindowOperations.h"
#include "../Math/ColorPalette.h"
#include "../Rendering/Renderer.h"
#include "Canvas.h"

Panel::Panel()
{

}

Panel::Panel(GameObject* gameObject)
{
	this->gameObject = gameObject;

	this->roundedPixels = 3;
	this->color = ColorPalette::Gray;
}

void Panel::Start()
{
	this->shader = ShaderReader::ReadShader(Project::experioResourcesPath + "/Standard/Shaders/ColorPanel.shader");
	this->wasTexturedLastFrame = false;
}

void Panel::Update()
{
	if (texture.IsNull())
	{
		if(wasTexturedLastFrame)
			this->shader = ShaderReader::ReadShader(Project::experioResourcesPath + "/Standard/Shaders/ColorPanel.shader");
		wasTexturedLastFrame = false;
		RenderColored();
	}
	else
	{
		if(!wasTexturedLastFrame)
			this->shader = ShaderReader::ReadShader(Project::experioResourcesPath + "/Standard/Shaders/TexturedPanel.shader");
		wasTexturedLastFrame = true;
		RenderTextured();
	}
}

void Panel::RenderColored()
{
	float canvasWidth = Canvas::GetCanvasWidth();
	float canvasHeight = Canvas::GetCanvasHeight();

	FRect rect = gameObject->GetCanvasSpaceRect();
	rect.min.x /= canvasWidth;
	rect.min.y /= canvasHeight;
	rect.max.x /= canvasWidth;
	rect.max.y /= canvasHeight;

	float cornerPoint = GetCornerPoint();

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

void Panel::RenderTextured()
{
	float canvasWidth = Canvas::GetCanvasWidth();
	float canvasHeight = Canvas::GetCanvasHeight();

	FRect rect = gameObject->GetCanvasSpaceRect();
	rect.min.x /= canvasWidth;
	rect.min.y /= canvasHeight;
	rect.max.x /= canvasWidth;
	rect.max.y /= canvasHeight;

	float cornerPoint = GetCornerPoint();

	texture->Bind(0);

	shader->Bind();
	shader->SetUniformInt("panelTexture", 0);
	shader->SetUniformVec2("minCorner", rect.min);
	shader->SetUniformVec2("maxCorner", rect.max);
	shader->SetUniformFloat("cornerPoint", cornerPoint);

	glm::vec2 verticies[6] = {
		rect.GetTopLeft(), rect.GetBottomLeft(), rect.GetTopRight(),
		rect.GetBottomRight(), rect.GetTopRight(), rect.GetBottomLeft()
	};

	glm::vec2 uvs[6] = {
		{0, 1}, {0, 0}, {1, 1},
		{1, 0}, {1, 1}, {0, 0}
	};

	VertexBuffer vertexBuffer(verticies, sizeof(verticies));
	VertexBuffer uvBuffer(uvs, sizeof(uvs));

	VertexArray va;

	VertexBufferLayout vertexLayout, uvLayout;
	vertexLayout.PushFloat(2);
	uvLayout.PushFloat(2);

	va.AddBuffer(&vertexBuffer, vertexLayout);
	va.AddBuffer(&uvBuffer, uvLayout);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

float Panel::GetCornerPoint()
{
	FWindowData data;
	data.width = Canvas::GetCanvasWidth();
	data.height = Canvas::GetCanvasHeight();
	return LWindowOperations::PixelToNormalizedSize(data, roundedPixels, EWindowAxisType::X);
}
