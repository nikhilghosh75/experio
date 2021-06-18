#pragma once

#include "../Framework/Framework.h"

class CheckBox : public Component
{
public:
	CheckBox();
	CheckBox(GameObject* gameObject);

	virtual void Start() override;

	virtual void Update() override;

	void RenderCheckBox();

	void HandleInput();

	FColor offColor;
	FColor onColor;

	bool isOn;

private:
	Shader* shader;
};