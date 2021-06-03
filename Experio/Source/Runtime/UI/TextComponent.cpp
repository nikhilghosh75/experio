#include "TextComponent.h"
#include "Canvas.h"
#include "UIQueue.h"
#include "../Debug/Debug.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/VertexBuffer.h"
#include "../Core/Window.h"
#include "../Core/LWindowOperations.h"
#include "../Rendering/VertexArray.h"
#include "../Rendering/VertexBufferLayout.h"
#include "../Rendering/Shaders/ShaderReader.h"

TextComponent::TextComponent()
{
}

TextComponent::TextComponent(GameObject * object)
{
	this->gameObject = object;
	this->fontSize = 36;
	this->horizontalWrapMode = EHorizontalWrapMode::Wrap;
	this->verticalWrapMode = EVerticalWrapMode::Truncate;
	this->horizontalAlignment = EHorizontalAlignment::Left;
	this->verticalAlignment = EVerticalAlignment::Upper;
	this->spacing = 1;
}

TextComponent::~TextComponent()
{
	if (verticies != nullptr)
		delete[] verticies;

	if (uvs != nullptr)
		delete[] uvs;
}

void TextComponent::Start()
{
	SetDefaultShader();

	SetCapacity(6);
}

void TextComponent::Update()
{
	UIQueue::AddToQueue(this, gameObject->rectTransform.z, EUIComponentType::TextComponent);
}

void TextComponent::SetDefaultShader()
{
	shader = Renderer::textShader;
}

void TextComponent::SetCapacity(uint32_t newCapacity)
{
	if (verticies != nullptr)
		delete[] verticies;

	if (uvs != nullptr)
		delete[] uvs;

	if (offsets != nullptr)
		delete[] offsets;

	verticies = new glm::vec2[6 * newCapacity];
	uvs = new glm::vec2[6 * newCapacity];
	offsets = new glm::vec2[6 * newCapacity];

	capacity = newCapacity;
}

void TextComponent::RenderText()
{
	if (shader == nullptr)
	{
		SetDefaultShader();
	}

	if (font.IsNull())
	{
		Debug::LogError("Text could not be rendered due to it not having a font");
		return;
	}

	if (text.empty())
	{
		return;
	}

	SetupRendering();

	float canvasWidth = Canvas::GetCanvasWidth();
	float canvasHeight = Canvas::GetCanvasHeight();

	FRect rect = gameObject->GetCanvasSpaceRect();
	rect.min.x /= canvasWidth;
	rect.min.y /= canvasHeight;
	rect.max.x /= canvasWidth;
	rect.max.y /= canvasHeight;

	FWindowData data(canvasWidth, canvasHeight);

	float clippedSize = LWindowOperations::PixelToNormalizedSize(data, fontSize * 1.333f, EWindowAxisType::Y);
	float clippedSpacing = LWindowOperations::PixelToNormalizedSize(data, spacing * 2, EWindowAxisType::Y);
	float clippedMargin = LWindowOperations::PixelToNormalizedSize(data, margins, EWindowAxisType::X);
	FVector2 topLeftOfText = rect.GetTopLeft();
	FVector2 currentCursorLocation = topLeftOfText + FVector2(clippedMargin, -clippedMargin);

	unsigned int bitmapWidth = font->GetBitmapWidth();

	unsigned int actualLength = 0;

	for (unsigned int i = 0; i < text.size(); i++)
	{
		if (ShouldStopRendering(currentCursorLocation, rect))
			break;

		char charCode = text[i];
		FCharacterInfo charInfo = font->GetCharacterFromCode(charCode);

		FVector2 charOffset = LWindowOperations::PixelToNormalizedPos(data, charInfo.offset);
		float charPixelWidth = charInfo.uvCoordinates.GetWidth() * bitmapWidth * fontSize / font->defaultFontSize;
		float charWidth = LWindowOperations::PixelToNormalizedSize(data, charPixelWidth, EWindowAxisType::X);
		lineInfos.back().width += charWidth;
		lineInfos.back().numCharacters++;
		
		glm::vec2 vertexUpLeft = glm::vec2(currentCursorLocation.x + charOffset.x, currentCursorLocation.y - charOffset.y);
		glm::vec2 vertexUpRight = glm::vec2(currentCursorLocation.x + charOffset.x + charWidth, currentCursorLocation.y - charOffset.y);
		glm::vec2 vertexDownLeft = glm::vec2(currentCursorLocation.x + charOffset.x, currentCursorLocation.y - clippedSize);
		glm::vec2 vertexDownRight = glm::vec2(currentCursorLocation.x + charOffset.x + charWidth, currentCursorLocation.y - clippedSize);

		SetVertices(i, vertexUpLeft, vertexUpRight, vertexDownLeft, vertexDownRight);

		FVector2 uvMin = charInfo.uvCoordinates.min;
		FVector2 uvMax = charInfo.uvCoordinates.max;
		SetUVs(i, uvMin, uvMax);
		
		currentCursorLocation = GetNextCursorPosition(currentCursorLocation, rect, clippedSize, clippedSpacing, charInfo, data);

		actualLength++;
	}

	SetOffsets(clippedMargin, rect, clippedSize, clippedSpacing);

	VertexBuffer vertexBuffer(verticies, sizeof(glm::vec2) * actualLength * 6, false);
	VertexBuffer uvBuffer(uvs, sizeof(glm::vec2) * actualLength * 6, false);
	VertexBuffer offsetBuffer(offsets, sizeof(glm::vec2) * actualLength * 6, false);

	VertexBufferLayout vertexLayout, uvLayout, offsetLayout;
	vertexLayout.PushFloat(2);
	uvLayout.PushFloat(2);
	offsetLayout.PushFloat(2);

	VertexArray va;
	va.Bind();
	va.AddBuffer(&vertexBuffer, vertexLayout);
	va.AddBuffer(&uvBuffer, uvLayout);
	va.AddBuffer(&offsetBuffer, offsetLayout);

	shader->Bind();
	shader->SetUniformInt("textureSampler", 10);
	shader->SetUniformVec4("textColor", glm::vec4(color.r, color.g, color.b, color.a));
	font->fontTexture->Bind(10);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, 6 * actualLength);

	glDisable(GL_BLEND);
}

bool TextComponent::IsSpecialChar(char c) const
{
	return c == 32;
}

void TextComponent::SetupRendering()
{
	unsigned int length = this->text.size();

	if (length > capacity)
		SetCapacity(length + 1);

	lineInfos.clear();
	lineInfos.emplace_back();
}

void TextComponent::SetVertices(unsigned int i, glm::vec2 upLeft, glm::vec2 upRight, glm::vec2 downLeft, glm::vec2 downRight)
{
	verticies[i * 6] = upLeft;
	verticies[i * 6 + 1] = downLeft;
	verticies[i * 6 + 2] = upRight;
	verticies[i * 6 + 3] = downRight;
	verticies[i * 6 + 4] = upRight;
	verticies[i * 6 + 5] = downLeft;
}

void TextComponent::SetUVs(unsigned int i, FVector2 uvMin, FVector2 uvMax)
{
	uvs[i * 6] = glm::vec2(uvMin.x, uvMin.y);
	uvs[i * 6 + 1] = glm::vec2(uvMin.x, uvMax.y);
	uvs[i * 6 + 2] = glm::vec2(uvMax.x, uvMin.y);
	uvs[i * 6 + 3] = glm::vec2(uvMax.x, uvMax.y);
	uvs[i * 6 + 4] = glm::vec2(uvMax.x, uvMin.y);
	uvs[i * 6 + 5] = glm::vec2(uvMin.x, uvMax.y);
}

void TextComponent::SetOffsets(float clippedMargins, FRect rect, float clippedSize, float clippedSpacing)
{
	if (lineInfos.back().numCharacters == 0)
		lineInfos.pop_back();

	for (unsigned int i = 0; i < capacity * 6; i++)
	{
		offsets[i] = glm::vec2(0, 0);
	}

	if (horizontalAlignment == EHorizontalAlignment::Middle)
		SetOffsetsHorizontalMiddle(clippedMargins, rect);
	else if (horizontalAlignment == EHorizontalAlignment::Right)
		SetOffsetsHorizontalRight(clippedMargins, rect);

	if (verticalAlignment == EVerticalAlignment::Middle)
		SetOffsetsVerticalMiddle(clippedMargins, rect, clippedSize, clippedSpacing);
	else if (verticalAlignment == EVerticalAlignment::Bottom)
		SetOffsetsVerticalBottom(clippedMargins, rect, clippedSize, clippedSpacing);
}

void TextComponent::SetOffsetsHorizontalMiddle(float clippedMargins, FRect rect)
{
	unsigned int currentCharacter = 0;
	float rectWidth = rect.GetWidth();

	for (size_t i = 0; i < lineInfos.size(); i++)
	{
		float offsetBy = (rectWidth - lineInfos[i].width) / 2 + clippedMargins;
		for (size_t j = 0; j < lineInfos[i].numCharacters; j++)
		{
			offsets[(currentCharacter + j) * 6].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 1].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 2].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 3].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 4].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 5].x = offsetBy;
		}
		currentCharacter += lineInfos[i].numCharacters;
	}
}

void TextComponent::SetOffsetsHorizontalRight(float clippedMargins, FRect rect)
{
	unsigned int currentCharacter = 0;
	float rectWidth = rect.GetWidth();

	for (size_t i = 0; i < lineInfos.size(); i++)
	{
		float offsetBy = rectWidth - lineInfos[i].width - clippedMargins;
		for (size_t j = 0; j < lineInfos[i].numCharacters; j++)
		{
			offsets[(currentCharacter + j) * 6].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 1].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 2].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 3].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 4].x = offsetBy;
			offsets[(currentCharacter + j) * 6 + 5].x = offsetBy;
		}
		currentCharacter += lineInfos[i].numCharacters;
	}
}

void TextComponent::SetOffsetsVerticalMiddle(float clippedMargins, FRect rect, float clippedSize, float clippedSpacing)
{
	float rectHeight = rect.GetHeight();
	float lineHeight = clippedSize + clippedSpacing;
	float offsetBy = (rectHeight - lineHeight * lineInfos.size()) / 2 + clippedMargins;

	for (unsigned int i = 0; i < capacity * 6; i++)
	{
		offsets[i].y = -offsetBy;
	}
}

void TextComponent::SetOffsetsVerticalBottom(float clippedMargins, FRect rect, float clippedSize, float clippedSpacing)
{
	float rectHeight = rect.GetHeight();
	float lineHeight = clippedSize + clippedSpacing;
	float offsetBy = rectHeight - lineHeight - clippedMargins;

	for (unsigned int i = 0; i < capacity * 6; i++)
	{
		offsets[i].y = -offsetBy;
	}
}

FVector2 TextComponent::GetNextCursorPosition(FVector2 cursorPosition, FRect rect, float clippedSize, float clippedSpacing, const FCharacterInfo& charInfo, const FWindowData& data)
{
	int xAdvance = charInfo.xAdvance * fontSize / font->defaultFontSize;
	float clippedXAdvance = LWindowOperations::PixelToNormalizedSize(data, xAdvance, EWindowAxisType::X);

	if (horizontalWrapMode == EHorizontalWrapMode::Wrap)
	{
		if (cursorPosition.x + clippedXAdvance > rect.max.x)
		{
			float clippedMargin = LWindowOperations::PixelToNormalizedSize(data, margins, EWindowAxisType::X);
			lineInfos.emplace_back();
			return FVector2(rect.min.x + clippedMargin, cursorPosition.y - clippedSize - clippedSpacing);
		}
	}

	FVector2 cursorMoveVec = FVector2(clippedXAdvance, 0);
	lineInfos.back().width += clippedXAdvance;
	return cursorPosition + cursorMoveVec;
}

bool TextComponent::ShouldStopRendering(FVector2 cursorPosition, FRect rect) const
{
	if (verticalWrapMode == EVerticalWrapMode::Truncate)
	{
		return cursorPosition.y < rect.GetBottomLeft().y;
	}
	return false;
}
