#pragma once
#include "RectTransform.h"
#include <string>
#include "../Files/Font/FontReader.h"
#include "../Rendering/Shader.h"

class TextComponent 
{
public:
	TextComponent();

	RectTransform transform;

	float margins = 4;

	int fontSize;
	std::string text;
	FontData* font;
	Shader* shader;

	void SetDefaultShader();

	void RenderText();
};