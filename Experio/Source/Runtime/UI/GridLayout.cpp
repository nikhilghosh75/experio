#include "GridLayout.h"

GridLayout::GridLayout()
{
	this->gameObject = nullptr;
}

GridLayout::GridLayout(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

void GridLayout::Start()
{
}

void GridLayout::Update()
{
	FRect rect = gameObject->GetCanvasSpaceRect();
	size_t numChildren = gameObject->children.size();

	float sqrtChildren = LMath::Sqrt(numChildren);
	size_t numRows = LMath::Ceil(sqrtChildren);
	size_t numColumns = LMath::Ceil(sqrtChildren);

	float cellWidth = rect.GetWidth() / numColumns;
	float cellHeight = rect.GetHeight() / numRows;

	size_t columnCount = 0;
	size_t rowCount = 0;

	for (int i = 0; i < numChildren; i++)
	{
		columnCount = i % numColumns;
		rowCount = i / numColumns;

		GameObject* current = gameObject->children[i];
		
		current->rectTransform.xConstraint.type = EPositionConstraintType::Pixel;
		current->rectTransform.xConstraint.value = columnCount * cellWidth;
		
		current->rectTransform.yConstraint.type = EPositionConstraintType::Pixel;
		current->rectTransform.yConstraint.value = rowCount * cellHeight;

		current->rectTransform.widthConstraint.type = EDimensionConstraintType::Constant;
		current->rectTransform.widthConstraint.value = cellWidth;

		current->rectTransform.heightConstraint.type = EDimensionConstraintType::Constant;
		current->rectTransform.heightConstraint.value = cellHeight;
	}
}
