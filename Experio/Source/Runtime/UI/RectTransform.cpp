#include "RectTransform.h"

RectTransform::RectTransform()
{

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
