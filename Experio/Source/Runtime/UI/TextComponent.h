#pragma once
#include "RectTransform.h"
#include <string>
#include "../Files/Font/FontReader.h"
#include "../Framework/Framework.h"
#include "../Math/FColor.h"
#include "../Rendering/Shaders/Shader.h"
#include "../Rendering/Managers/FontManager.h"

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

	float margins = 4;

	int fontSize;
	FontRef font;
	std::string text;
	FColor color;
	Shader* shader;

	void SetDefaultShader();

	void RenderText();
};