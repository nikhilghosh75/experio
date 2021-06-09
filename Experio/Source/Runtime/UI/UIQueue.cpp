#include "UIQueue.h"
#include "../DefaultComponents.h"
#include "../Input/Input.h"

THeap<FUIQueueSlot, std::greater<FUIQueueSlot>> UIQueue::renderQueue;
THeap<FUIQueueSlot, std::less<FUIQueueSlot>> UIQueue::inputQueue;

FUIQueueSlot::FUIQueueSlot()
{
	this->component = nullptr;
	this->z = -1500;
	this->componentType = EUIComponentType::None;
}

FUIQueueSlot::FUIQueueSlot(Component* component, float z, EUIComponentType componentType)
{
	this->component = component;
	this->z = z;
	this->componentType = componentType;
}

FUIQueueSlot::~FUIQueueSlot()
{
}

void UIQueue::AddToQueue(Component* component, float z, EUIComponentType componentType)
{
	renderQueue.Emplace(component, z, componentType);
	inputQueue.Emplace(component, z, componentType);
}

void UIQueue::RenderUI()
{
	HandleInput();

	uint32_t numElements = renderQueue.Count();
	for (uint32_t i = 0; i < numElements; i++)
	{
		RenderUISlot(renderQueue.First());
		renderQueue.Pop();
	}

	renderQueue.Empty();
	inputQueue.Empty();
}

void UIQueue::HandleInput()
{
	uint32_t numElements = inputQueue.Count();
	for (uint32_t i = 0; i < numElements; i++)
	{
		FUIQueueSlot slot = inputQueue.First();
		FRect rect = slot.component->GetGameObject()->GetCanvasSpaceRect();
		FVector2 mousePosition = Input::GetMousePosition();
		bool isOverElement = rect.IsInside(mousePosition);

		if (isOverElement)
		{
			HandleElementInput(slot);
			return;
		}

		inputQueue.Pop();
	}
}

void UIQueue::HandleElementInput(const FUIQueueSlot& slot)
{
	switch (slot.componentType)
	{
	case EUIComponentType::Button:
		((Button*)slot.component)->HandleInput(); break;
	}
}

void UIQueue::RenderUISlot(const FUIQueueSlot& slot)
{
	switch (slot.componentType)
	{
	case EUIComponentType::Button:
		((Button*)slot.component)->RenderButton(); break;
	case EUIComponentType::ImageComponent:
		((ImageComponent*)slot.component)->RenderImage(); break;
	case EUIComponentType::Panel:
		((Panel*)slot.component)->RenderPanel(); break;
	case EUIComponentType::ProgressBar:
		((ProgressBar*)slot.component)->RenderProgressBar(); break;
	case EUIComponentType::TextComponent:
		((TextComponent*)slot.component)->RenderText(); break;
	}
}
