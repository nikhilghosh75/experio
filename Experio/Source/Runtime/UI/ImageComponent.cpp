#include "ImageComponent.h"
#include "Canvas.h"
#include "../Rendering/Renderer.h"
#include "../Core/Window.h"

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

	Renderer::Get()->DrawQuad(*texture, nullptr, imageUVRect, rect);
}
