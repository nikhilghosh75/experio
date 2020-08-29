#pragma once
#include "../Math/FRect.h"

class RectTransform
{
public:
	RectTransform();
	RectTransform(FVector2 min, FVector2 max);

	FRect rect;

	// Add Dynamic Rect Design
};