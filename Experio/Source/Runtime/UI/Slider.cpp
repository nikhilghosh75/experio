#include "Slider.h"
#include "UIQueue.h"

Slider::Slider()
{
	this->gameObject = nullptr;
}

Slider::Slider(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

void Slider::Start()
{
	
}

void Slider::Update()
{
	UIQueue::AddToQueue(this, gameObject->rectTransform.z, EUIComponentType::Slider);
}

void Slider::RenderSlider()
{
}

void Slider::HandleInput()
{
}
