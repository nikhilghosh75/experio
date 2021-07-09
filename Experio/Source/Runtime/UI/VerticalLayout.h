#pragma once

#include "../Framework/Framework.h"

class VerticalLayout : public Component
{
public:
	VerticalLayout();

	VerticalLayout(GameObject* gameObject);

	virtual void Start() override;

	virtual void Update() override;

	float margins;
};