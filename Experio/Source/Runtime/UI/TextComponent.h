#pragma once
#include "RectTransform.h"
#include <string>
#include "../Files/Font/FontReader.h"
#include "../Rendering/Shaders/Shader.h"
#include "../Rendering/Managers/FontManager.h"
#include "../Framework/Framework.h"

enum class ETextRenderMode
{
	Default,
	Stylized,
	Rich
};

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
	FontRef font;
	Shader* shader;

	void SetDefaultShader();

	void RenderText();
};