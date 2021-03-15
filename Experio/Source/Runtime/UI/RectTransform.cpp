#include "RectTransform.h"

RectTransform::RectTransform()
{
	this->rect = FRect();
	this->pivot = FVector2(0.5f, 0.5f);
	this->rotation = 0;
	this->anchorType = EAnchorType::Center;
}

RectTransform::RectTransform(FVector2 min, FVector2 max)
{
	this->rect = FRect(min, max);
	this->pivot = FVector2(0.5f, 0.5f);
	this->rotation = 0;
	this->anchorType = EAnchorType::Center;
}

RectTransform::RectTransform(FVector2 min, FVector2 max, FVector2 pivot)
{
	this->rect = FRect(min, max);
	this->pivot = pivot;
	this->rotation = 0;
	this->anchorType = EAnchorType::Center;
}

RectTransform::RectTransform(FVector2 min, FVector2 max, FVector2 pivot, float rotation)
{
	this->rect = FRect(min, max);
	this->pivot = pivot;
	this->rotation = rotation;
	this->anchorType = EAnchorType::Center;
}

bool RectTransform::IsFillAnchorType(EAnchorType anchorType)
{
	if (anchorType == EAnchorType::Bottom || anchorType == EAnchorType::Center
		|| anchorType == EAnchorType::Full || anchorType == EAnchorType::Left
		|| anchorType == EAnchorType::Middle || anchorType == EAnchorType::Right
		|| anchorType == EAnchorType::Upper)
	{
		return true;
	}
	return false;
}

FRect RectTransform::MergeRectTransform(FRect rect, FRect childToParent, EAnchorType childAnchorType, FVector2 screenDimensions)
{
	switch (childAnchorType)
	{
	case EAnchorType::Full: return MergeRectFull(rect, childToParent, screenDimensions);
	}
}

FRect RectTransform::MergeRectFull(FRect rect, FRect childToParent, FVector2 screenDimensions)
{
	FRect newRect;

	if (rect.min.x < 0)
	{
		newRect.min = rect.min + childToParent.min;
		newRect.max = rect.max + childToParent.max;
	}
	else
	{
		
	}

	return newRect;
}

