#pragma once
#include "../Containers/THeap.h"
#include "../Framework/Component.h"
#include <stdint.h>

enum class EUISortMode : uint8_t
{
	Custom,
	Unity
};

enum class EUIComponentType : uint16_t
{
	None = 0,
	Custom = 1,
	TextComponent = 104,
	ImageComponent = 105,
	ProgressBar = 106,
	Panel = 107,
	Button = 108,
	Checkbox = 109
};

struct FUIQueueSlot
{
	Component* component;
	float z;
	EUIComponentType componentType;

	FUIQueueSlot();
	FUIQueueSlot(Component* component, float z, EUIComponentType componentType);
	~FUIQueueSlot();

	bool operator<(const FUIQueueSlot& slot) const { return this->z < slot.z; }
	bool operator>(const FUIQueueSlot& slot) const { return this->z > slot.z; }
};

class UIQueue
{
	static THeap<FUIQueueSlot, std::greater<FUIQueueSlot>> queue;

public:
	static void AddToQueue(Component* component, float z, EUIComponentType componentType);

	static void RenderUI();

private:
	static void RenderUISlot(const FUIQueueSlot& slot);
};