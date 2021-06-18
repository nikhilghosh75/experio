#pragma once

#include "../Framework/Framework.h"

class Slider : public Component
{
public:
	Slider();
	Slider(GameObject* gameObject);

	virtual void Start() override;
	
	virtual void Update() override;

	void RenderSlider();

	void HandleInput();

	float value;
};