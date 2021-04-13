#include "RectTransform.h"

RectTransform::RectTransform()
{

}

void RectTransform::SetXConstraint(EPositionConstraintType type, float value)
{
	xConstraint.type = type;
	xConstraint.value = value;
}

void RectTransform::SetXConstraint(const char* type, float value)
{
	xConstraint.type = PositionConstraintTypeFromText(type);
	xConstraint.value = value;
}

void RectTransform::SetYConstraint(EPositionConstraintType type, float value)
{
	yConstraint.type = type;
	yConstraint.value = value;
}

void RectTransform::SetYConstraint(const char* type, float value)
{
	yConstraint.type = PositionConstraintTypeFromText(type);
	yConstraint.value = value;
}

void RectTransform::SetWidthConstraint(EDimensionConstraintType type, float value)
{
	widthConstraint.type = type;
	widthConstraint.value = value;
}

void RectTransform::SetWidthConstraint(const char* type, float value)
{
	widthConstraint.type = DimensionConstraintTypeFromText(type);
	widthConstraint.value = value;
}

void RectTransform::SetHeightConstraint(EDimensionConstraintType type, float value)
{
	heightConstraint.type = type;
	heightConstraint.value = value;
}

void RectTransform::SetHeightConstraint(const char* type, float value)
{
	heightConstraint.type = DimensionConstraintTypeFromText(type);
	heightConstraint.value = value;
}

float MergePositionConstraint(float position, PositionConstraint constraint)
{
	switch (constraint.type)
	{
	case EPositionConstraintType::Center: return position;
	case EPositionConstraintType::Pixel: return position + constraint.value;
	}
	return 0.0f;
}

float MergeDimensionConstraint(float dimension, DimensionConstraint constraint)
{
	switch (constraint.type)
	{
	case EDimensionConstraintType::Constant: return constraint.value;
	case EDimensionConstraintType::Fill: return dimension * constraint.value;
	}
	return 0;
}

const char* ConstraintTextFromType(EPositionConstraintType type)
{
	switch (type)
	{
	case EPositionConstraintType::Center: return "Center";
	case EPositionConstraintType::Pixel: return "Pixel";
	}
	return "";
}

const char* ConstraintTextFromType(EDimensionConstraintType type)
{
	switch (type)
	{
	case EDimensionConstraintType::Constant: return "Constant";
	case EDimensionConstraintType::Fill: return "Fill";
	}
	return "";
}

EPositionConstraintType PositionConstraintTypeFromText(const char* type)
{
	if (strcmp(type, "Center") == 0) return EPositionConstraintType::Center;
	if (strcmp(type, "Pixel") == 0) return EPositionConstraintType::Pixel;
	return EPositionConstraintType();
}

EDimensionConstraintType DimensionConstraintTypeFromText(const char* type)
{
	if (strcmp(type, "Constant") == 0) return EDimensionConstraintType::Constant;
	if (strcmp(type, "Fill") == 0) return EDimensionConstraintType::Fill;
	return EDimensionConstraintType();
}
