#pragma once
#include "../Math/FRect.h"
#include "../Math/FVector2.h"

enum class EAnchorType : uint8_t
{
	Upper,
	UpperLeft,
	UpperCenter,
	UpperRight,
	Middle,
	MiddleLeft,
	MiddleCenter,
	MiddleRight,
	Bottom,
	BottomLeft,
	BottomCenter,
	BottomRight,
	Left,
	Center,
	Right,
	Full
};

class RectTransform
{
public:
	friend class GameObject;

	RectTransform();
	RectTransform(FVector2 min, FVector2 max);
	RectTransform(FVector2 min, FVector2 max, FVector2 pivot);
	RectTransform(FVector2 min, FVector2 max, FVector2 pivot, float rotation);

	FRect rect;
	float rotation;
	FVector2 pivot;
	EAnchorType anchorType;

private:
	static bool IsFillAnchorType(EAnchorType anchorType);

	static FRect MergeRectTransform(FRect rect, FRect childToParent, EAnchorType childAnchorType, FVector2 screenDimensions);

	static FRect MergeRectFull(FRect rect, FRect childToParent, FVector2 screenDimensions);

	static FRect MergeRectWithScreen(FRect rect, FVector2 screenDimensions);
};