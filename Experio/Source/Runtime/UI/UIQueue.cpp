#include "UIQueue.h"
#include "../DefaultComponents.h"

THeap<FUIQueueSlot, std::greater<FUIQueueSlot>> UIQueue::queue;

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
	queue.Emplace(component, z, componentType);
}

void UIQueue::RenderUI()
{
	uint32_t numElements = queue.Count();
	for (uint32_t i = 0; i < numElements; i++)
	{
		RenderUISlot(queue.First());
		queue.Pop();
	}
}

void UIQueue::RenderUISlot(const FUIQueueSlot& slot)
{
	switch (slot.componentType)
	{
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
