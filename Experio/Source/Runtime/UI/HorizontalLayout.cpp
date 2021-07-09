#include "HorizontalLayout.h"

HorizontalLayout::HorizontalLayout()
{
	this->gameObject = nullptr;
}

HorizontalLayout::HorizontalLayout(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

void HorizontalLayout::Start()
{

}

void HorizontalLayout::Update()
{
	FRect rect = gameObject->GetCanvasSpaceRect();

	size_t numChildren = gameObject->children.size();
	for (size_t i = 0; i < numChildren; i++)
	{
		GameObject* current = gameObject->children[i];
		current->rectTransform.xConstraint.type = EPositionConstraintType::Pixel;
		current->rectTransform.xConstraint.value = i * rect.GetWidth() / numChildren;
		current->rectTransform.widthConstraint.type = EDimensionConstraintType::Constant;
		current->rectTransform.widthConstraint.value = rect.GetWidth() / numChildren;
	}
}
