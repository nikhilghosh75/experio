#include "RectTransform.h"

RectTransform::RectTransform()
{
}

RectTransform::RectTransform(FVector2 min, FVector2 max)
{
	this->rect = FRect(min, max);
}
