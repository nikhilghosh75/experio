#include "ImageComponent.h"
#include "Canvas.h"
#include "../Rendering/Renderer.h"
#include "../Core/Window.h"
#include "../Rendering/Shaders/ShaderReader.h"

const FRect ImageComponent::imageUVRect = FRect(0, 0, 1, 1);

ImageComponent::ImageComponent()
{
	this->gameObject = nullptr;
}

ImageComponent::ImageComponent(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

void ImageComponent::Start()
{
	shader = Renderer::imageShader;
}

void ImageComponent::Update()
{
	if (texture.IsNull())
		return;

	float canvasWidth = Canvas::GetCanvasWidth();
	float canvasHeight = Canvas::GetCanvasHeight();

	FRect rect = gameObject->GetCanvasSpaceRect();
	rect.min.x /= canvasWidth;
	rect.min.y /= canvasHeight;
	rect.max.x /= canvasWidth;
	rect.max.y /= canvasHeight;

	Renderer::Get()->SetBlend(true, EBlendFunc::OneMinusSourceColor);

	shader->Bind();
	shader->SetUniformVec4("imageTint", glm::vec4(tint.r, tint.g, tint.b, tint.a));

	Renderer::Get()->DrawQuad(*texture, shader, imageUVRect, rect);
}
