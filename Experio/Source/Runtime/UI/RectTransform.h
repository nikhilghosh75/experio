#pragma once
#include "../Math/FRect.h"
#include "../Math/FVector2.h"

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

EPositionConstraintType PositionConstraintTypeFromText(const char* type);
EDimensionConstraintType DimensionConstraintTypeFromText(const char* type);

class RectTransform
{
public:
	friend class GameObject;

	PositionConstraint xConstraint;
	PositionConstraint yConstraint;
	DimensionConstraint widthConstraint;
	DimensionConstraint heightConstraint;

	RectTransform();

	void SetXConstraint(EPositionConstraintType type, float value);
	void SetXConstraint(const char* type, float value);

	void SetYConstraint(EPositionConstraintType type, float value);
	void SetYConstraint(const char* type, float value);

	void SetWidthConstraint(EDimensionConstraintType type, float value);
	void SetWidthConstraint(const char* type, float value);

	void SetHeightConstraint(EDimensionConstraintType type, float value);
	void SetHeightConstraint(const char* type, float value);
};