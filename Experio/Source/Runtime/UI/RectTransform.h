#pragma once
#include "../Math/FRect.h"
#include "../Math/FVector2.h"

/*
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
*/

enum class EPositionConstraintType : uint8_t
{
	Center,
	Pixel,
};

enum class EDimensionConstraintType : uint8_t
{
	Fill,
	Constant
};

// For X and Y position
class PositionConstraint
{
public:
	EPositionConstraintType type;
	float value;
};

// For Width and Height
class DimensionConstraint
{
public:
	EDimensionConstraintType type;
	float value;
};

float MergePositionConstraint(float position, PositionConstraint constraint);
float MergeDimensionConstraint(float dimension, DimensionConstraint constraint);

const char* ConstraintTextFromType(EPositionConstraintType type);
const char* ConstraintTextFromType(EDimensionConstraintType type);

class RectTransform
{
public:
	friend class GameObject;

	PositionConstraint xConstraint;
	PositionConstraint yConstraint;
	DimensionConstraint widthConstraint;
	DimensionConstraint heightConstraint;

	RectTransform();

};