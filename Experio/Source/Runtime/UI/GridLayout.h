#pragma once

#include "../Framework/Framework.h"

class GridLayout : public Component
{
public:
	GridLayout();

	GridLayout(GameObject* gameObject);

	virtual void Start() override;

	virtual void Update() override;

	float margins;
};