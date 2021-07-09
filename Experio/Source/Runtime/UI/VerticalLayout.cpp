#include "VerticalLayout.h"

VerticalLayout::VerticalLayout()
{
	this->gameObject = nullptr;
}

VerticalLayout::VerticalLayout(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

void VerticalLayout::Start()
{

}

void VerticalLayout::Update()
{
	FRect rect = gameObject->GetCanvasSpaceRect();

	size_t numChildren = gameObject->children.size();
	for (size_t i = 0; i < numChildren; i++)
	{
		GameObject* current = gameObject->children[i];
		current->rectTransform.yConstraint.type = EPositionConstraintType::Pixel;
		current->rectTransform.yConstraint.value = i * rect.GetHeight() / numChildren;
		current->rectTransform.heightConstraint.type = EDimensionConstraintType::Constant;
		current->rectTransform.heightConstraint.value = rect.GetHeight() / numChildren;
	}
}
