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

enum class EHorizontalAlignment : uint8_t
{
	Left,
	Middle,
	Right
};

enum class EVerticalAlignment : uint8_t
{
	Upper,
	Middle,
	Bottom
};

class TextComponent : public Component
{
public:
	TextComponent();
	TextComponent(GameObject* object);

	~TextComponent();

	virtual void Start() override;
	virtual void Update() override;

	void RenderText();

	float margins = 4;

	int fontSize;
	FontRef font;
	std::string text;
	FColor color;
	EHorizontalWrapMode horizontalWrapMode;
	EVerticalWrapMode verticalWrapMode;
	EHorizontalAlignment horizontalAlignment;
	EVerticalAlignment verticalAlignment;
	EFontType textType;
	float spacing;
	Shader* shader;

	void SetDefaultShader();

	void SetTextType(EFontType textType);

private:
	struct LineInfo
	{
		float width;
		unsigned int numCharacters;

		LineInfo() : width(0), numCharacters(0) {};
		LineInfo(float newWidth, unsigned int newNumCharacters) : width(newWidth), numCharacters(newNumCharacters) {};
	};

	glm::vec2* verticies = nullptr;
	glm::vec2* uvs = nullptr;
	glm::vec2* offsets = nullptr;

	std::vector<LineInfo> lineInfos;

	uint32_t capacity = 0;

	void SetCapacity(uint32_t newCapacity);

	bool IsSpecialChar(char c) const;

	void SetupRendering();

	void SetVertices(unsigned int i, glm::vec2 upLeft, glm::vec2 upRight, glm::vec2 downLeft, glm::vec2 downRight);

	void SetUVs(unsigned int i, FVector2 uvMin, FVector2 uvMax);

	void SetOffsets(float clippedMargins, FRect rect, float clippedSize, float clippedSpacing);

	void SetOffsetsHorizontalMiddle(float clippedMargins, FRect rect);
	void SetOffsetsHorizontalRight(float clippedMargins, FRect rect);
	
	void SetOffsetsVerticalMiddle(float clippedMargins, FRect rect, float clippedSize, float clippedSpacing);
	void SetOffsetsVerticalBottom(float clippedMargins, FRect rect, float clippedSize, float clippedSpacing);

	FVector2 GetNextCursorPosition(FVector2 cursorPosition, FRect rect, float clippedSize, float clippedSpacing, const FCharacterInfo& charInfo, const FWindowData& data);

	bool ShouldStopRendering(FVector2 cursorPosition, FRect rect) const;
};