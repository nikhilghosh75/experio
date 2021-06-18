#include "ProgressBar.h"
#include "Canvas.h"
#include "UIQueue.h"
#include "../Rendering/IndexBuffer.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/VertexBuffer.h"
#include "../Rendering/VertexBufferLayout.h"
#include "../Math/LMath.h"

static unsigned int indices[12] = { 
	0, 1, 2, 
	2, 3, 0, 
	4, 5, 6, 
	6, 7, 4 
};

ProgressBar::ProgressBar()
{
}

ProgressBar::ProgressBar(GameObject* gameObject)
{
	this->gameObject = gameObject;

	this->minValue = 0;
	this->maxValue = 1;
	this->value = 0.5;

	this->mode = EProgressBarMode::Vertical;
	this->crossFill = 0.6;
}

void ProgressBar::Start()
{
	this->shader = Renderer::progressBarShader;
}

void ProgressBar::Update()
{
	UIQueue::AddToQueue(this, gameObject->rectTransform.z, EUIComponentType::ProgressBar);
}

float ProgressBar::GetProgressFill()
{
	return LMath::Clamp((value - minValue) / (maxValue - minValue), 0, 1);
}

void ProgressBar::FillHorizontalProgressBar(FRect rect)
{
	float width = rect.GetWidth();
	float height = rect.GetHeight();
	float progressFill = GetProgressFill();

	vertices[0] = glm::vec2(rect.min.x, rect.min.y);
	vertices[1] = glm::vec2(rect.min.x, rect.max.y);
	vertices[2] = glm::vec2(rect.max.x, rect.max.y);
	vertices[3] = glm::vec2(rect.max.x, rect.min.y);
	vertices[4] = glm::vec2(rect.min.x, rect.min.y + height * crossFill);
	vertices[5] = glm::vec2(rect.min.y, rect.max.y - height * crossFill);
	vertices[6] = glm::vec2(rect.min.y + width * progressFill, rect.max.y - height * crossFill);
	vertices[7] = glm::vec2(rect.min.y + width * progressFill, rect.min.y + height * crossFill);
}

void ProgressBar::FillVerticalProgressBar(FRect rect)
{
	float width = rect.GetWidth();
	float height = rect.GetHeight();
	float progressFill = GetProgressFill();

	vertices[0] = glm::vec2(rect.min.x, rect.min.y);
	vertices[1] = glm::vec2(rect.min.x, rect.max.y);
	vertices[2] = glm::vec2(rect.max.x, rect.max.y);
	vertices[3] = glm::vec2(rect.max.x, rect.min.y);
	vertices[4] = glm::vec2(rect.min.x + width * crossFill, rect.min.y);
	vertices[5] = glm::vec2(rect.min.x + width * crossFill, rect.min.y + height * progressFill);
	vertices[6] = glm::vec2(rect.max.x - width * crossFill, rect.min.y + height * progressFill);
	vertices[7] = glm::vec2(rect.max.x - width * crossFill, rect.min.y);
}

void ProgressBar::FillColors()
{
	colors[0] = backgroundColor;
	colors[1] = backgroundColor;
	colors[2] = backgroundColor;
	colors[3] = backgroundColor;
	colors[4] = barColor;
	colors[5] = barColor;
	colors[6] = barColor;
	colors[7] = barColor;
}

void ProgressBar::RenderProgressBar()
{
	float canvasWidth = Canvas::GetCanvasWidth();
	float canvasHeight = Canvas::GetCanvasHeight();

	FRect rect = gameObject->GetCanvasSpaceRect();
	rect.min.x /= canvasWidth;
	rect.min.y /= canvasHeight;
	rect.max.x /= canvasWidth;
	rect.max.y /= canvasHeight;

	switch (mode)
	{
	case EProgressBarMode::Horizontal: FillHorizontalProgressBar(rect); break;
	case EProgressBarMode::Vertical: FillVerticalProgressBar(rect); break;
	}

	FillColors();
	RenderProgressBar();

	VertexBuffer vertexBuffer(vertices, sizeof(glm::vec2) * 8);
	VertexBuffer colorBuffer(colors, sizeof(FColor) * 8);

	IndexBuffer indexBuffer(indices, 12);

	VertexBufferLayout vertexLayout, colorLayout;
	vertexLayout.PushFloat(2);
	colorLayout.PushFloat(4);

	VertexArray va;
	va.Bind();
	va.AddBuffer(&vertexBuffer, vertexLayout);
	va.AddBuffer(&colorBuffer, colorLayout);

	shader->Bind();

	indexBuffer.Bind();

	Renderer::Get()->SetDepthTesting(false);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
}
