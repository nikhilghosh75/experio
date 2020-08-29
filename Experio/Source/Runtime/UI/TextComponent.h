#pragma once
#include "RectTransform.h"
#include <string>
#include "../Files/Font/FontReader.h"
#include "../Rendering/Shader.h"
#include "../Framework/Framework.h"

class TextComponent : public Component
{
public:
	TextComponent();
	TextComponent(GameObject* object);

	virtual void Start() override;
	virtual void Update() override;

	RectTransform transform;

	float margins = 4;

	int fontSize;
	std::string text;
	FontData* font;
	Shader* shader;

	void SetDefaultShader();

	void RenderText();
};