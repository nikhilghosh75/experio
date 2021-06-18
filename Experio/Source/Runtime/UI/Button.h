#pragma once

#include "../Framework/Framework.h"
#include "../Math/FColor.h"

class Button : public Component
{
public:
	Button();
	Button(GameObject* gameObject);

	virtual void Start() override;

	virtual void Update() override;

	void RenderButton();

	void HandleInput();

	FColor defaultColor;
	FColor hoveredColor;
	FColor activeColor;

	bool IsPressed() const { return isPressed; };

private:
	bool isPressed;
	bool isHovered;

	Shader* shader;
};