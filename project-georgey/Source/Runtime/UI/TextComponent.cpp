#include "TextComponent.h"
#include "../Debug/GDebug.h"
#include "../Rendering/VertexBuffer.h"
#include "../Core/GWindow.h"
#include "../Core/LWindowOperations.h"
#include "../Rendering/VertexArray.h"
#include "../Rendering/VertexBufferLayout.h"

TextComponent::TextComponent()
{
}

TextComponent::TextComponent(GameObject * object)
{
	this->gameObject = object;
	Start();
}

void TextComponent::Start()
{

}

void TextComponent::Update()
{
	RenderText();
}

void TextComponent::SetDefaultShader()
{
	shader = new Shader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/Text2DVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/Text2DFragment.shader");
	shader->Bind();
}

void TextComponent::RenderText()
{
	if (font == nullptr)
	{
		GDebug::LogError("Text could not be rendered due to it not having a font");
		return;
	}

	unsigned int length = this->text.size();
	
	glm::vec2* verticies = new glm::vec2[6 * length];
	glm::vec2* uvs = new glm::vec2[6 * length];

	FWindowData data = GWindow::GetWindowData();
	float clippedSize = LWindowOperations::PixelToNormalizedSize(data, fontSize * 1.333f, EWindowAxisType::Y);
	float clippedMargin = LWindowOperations::PixelToNormalizedSize(data, margins, EWindowAxisType::X);
	FVector2 topLeftOfText = this->transform.rect.GetTopLeft();
	FVector2 currentCursorLocation = topLeftOfText + FVector2(clippedMargin, -clippedMargin);

	for (int i = 0; i < length; i++)
	{
		char charCode = text[i];
		FCharacterInfo charInfo = font->GetCharacterFromCode(charCode);

		FVector2 charOffset = LWindowOperations::PixelToNormalizedPos(data, charInfo.offset);
		float charWidth = LWindowOperations::PixelToNormalizedSize(data, charInfo.uvCoordinates.GetWidth() * fontSize, EWindowAxisType::X) * 8;
		float chatHeight = LWindowOperations::PixelToNormalizedSize(data, charInfo.uvCoordinates.GetHeight() * fontSize, EWindowAxisType::Y);
		
		glm::vec2 vertexUpLeft = glm::vec2(currentCursorLocation.x + charOffset.x, currentCursorLocation.y - charOffset.y);
		glm::vec2 vertexUpRight = glm::vec2(currentCursorLocation.x + charOffset.x + charWidth, currentCursorLocation.y - charOffset.y);
		glm::vec2 vertexDownLeft = glm::vec2(currentCursorLocation.x + charOffset.x, currentCursorLocation.y - clippedSize);
		glm::vec2 vertexDownRight = glm::vec2(currentCursorLocation.x + charOffset.x + charWidth, currentCursorLocation.y - clippedSize);

		verticies[i * 6] = vertexUpLeft;
		verticies[i * 6 + 1] = vertexDownLeft;
		verticies[i * 6 + 2] = vertexUpRight;
		verticies[i * 6 + 3] = vertexDownRight;
		verticies[i * 6 + 4] = vertexUpRight;
		verticies[i * 6 + 5] = vertexDownLeft;

		FVector2 uvMin = charInfo.uvCoordinates.min;
		FVector2 uvMax = charInfo.uvCoordinates.max;

		uvs[i * 6] = glm::vec2(uvMin.x + 0.03f, 1.f - uvMin.y);
		uvs[i * 6 + 1] = glm::vec2(uvMin.x + 0.03f, 1.f - uvMax.y);
		uvs[i * 6 + 2] = glm::vec2(uvMax.x + 0.03f, 1.f - uvMin.y);
		uvs[i * 6 + 3] = glm::vec2(uvMax.x + 0.03f, 1.f - uvMax.y);
		uvs[i * 6 + 4] = glm::vec2(uvMax.x + 0.03f, 1.f - uvMin.y);
		uvs[i * 6 + 5] = glm::vec2(uvMin.x + 0.03f, 1.f - uvMax.y);
		
		//FVector2 cursorMoveVec = FVector2(LWindowOperations::PixelToNormalizedSize(data, charInfo.xAdvance * fontSize, EWindowAxisType::X), 0);
		FVector2 cursorMoveVec = FVector2(0.02f, 0);
		currentCursorLocation = currentCursorLocation + cursorMoveVec;
	}

	VertexBuffer vertexBuffer(verticies, sizeof(glm::vec2) * length * 6);
	VertexBuffer uvBuffer(uvs, sizeof(glm::vec2) * length * 6);

	VertexArray va;

	VertexBufferLayout vertexLayout, uvLayout;
	vertexLayout.PushFloat(2);
	uvLayout.PushFloat(2);

	va.Bind();
	va.AddBuffer(&vertexBuffer, vertexLayout);
	va.AddBuffer(&uvBuffer, uvLayout);

	shader->Bind();
	shader->SetUniformInt("textureSampler", 10);
	font->fontTexture->Bind(10);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, 6 * length);

	glDisable(GL_BLEND);

	delete[] verticies;
	delete[] uvs;
}
