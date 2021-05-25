#pragma once
#include "RectTransform.h"
#include <string>
#include "../Files/Font/FontReader.h"
#include "../Framework/Framework.h"
#include "../Math/FColor.h"
#include "../Rendering/Shaders/Shader.h"
#include "../Rendering/Managers/FontManager.h"

class FWindowData;

enum class ETextRenderMode
{
	Default,
	Stylized,
	Rich
};

enum class EHorizontalWrapMode : uint8_t
{
	Wrap,
	Overflow
};

enum class EVerticalWrapMode : uint8_t
{
	Truncate,
	Overflow
};

class TextComponent : public Component
{
public:
	TextComponent();
	TextComponent(GameObject* object);

	~TextComponent();

	virtual void Start() override;
	virtual void Update() override;

	float margins = 4;

	int fontSize;
	FontRef font;
	std::string text;
	FColor color;
	EHorizontalWrapMode horizontalWrapMode;
	EVerticalWrapMode verticalWrapMode;
	float spacing;
	Shader* shader;

	void SetDefaultShader();

private:
	glm::vec2* verticies = nullptr;
	glm::vec2* uvs = nullptr;
	glm::vec2* offsets = nullptr;

	std::vector<float> lineWidths;
	int numLines;

	uint32_t capacity = 0;

	void SetCapacity(uint32_t newCapacity);

	void RenderText();

	bool IsSpecialChar(char c) const;

	void SetupRendering();

	void SetVertices(unsigned int i, glm::vec2 upLeft, glm::vec2 upRight, glm::vec2 downLeft, glm::vec2 downRight);

	void SetUVs(unsigned int i, FVector2 uvMin, FVector2 uvMax);

	void SetOffsets();

	FVector2 GetNextCursorPosition(FVector2 cursorPosition, FRect rect, float clippedSize, float clippedSpacing, const FCharacterInfo& charInfo, const FWindowData& data);

	bool ShouldStopRendering(FVector2 cursorPosition, FRect rect) const;
};