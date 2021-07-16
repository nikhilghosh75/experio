#pragma once

#include <string>
#include "../Framework/Component.h"
#include "TextComponent.h"

class InputText : public Component
{
public:
	InputText();
	InputText(GameObject* gameObject);

	virtual void Start() override;

	virtual void Update() override;

	void HandleInput();

	std::string GetCurrentText() const { return currentText; }

	bool enableAlpha;
	bool enableNumeric;
	bool enableUppercase;
	bool enableLowercase;
	
	Shader* shader;

private:
	std::string currentText;
	TextComponent* textComponent;
	bool isSelected = false;

	void HandleKeyInput();

	bool ConvertToUpper(EKeyCode keyCode);
};