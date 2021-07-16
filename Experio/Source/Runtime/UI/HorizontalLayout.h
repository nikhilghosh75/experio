#pragma once

#include "../Framework/Framework.h"

class HorizontalLayout : public Component
{
public:
	HorizontalLayout();

	HorizontalLayout(GameObject* gameObject);

	virtual void Start() override;

	virtual void Update() override;

	float margins;
};