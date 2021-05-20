#pragma once

#include "../Framework/Framework.h"
#include "../Math/FColor.h"

enum class EProgressBarMode : uint8_t
{
	Horizontal,
	Vertical
};

class ProgressBar : public Component
{
public:
	ProgressBar();
	ProgressBar(GameObject* gameObject);

	float minValue;
	float maxValue;
	float value;

	virtual void Start() override;

	virtual void Update() override;

	FColor backgroundColor;
	FColor barColor;

	float crossFill;

	Shader* shader;

	EProgressBarMode mode;

private:
	glm::vec2 vertices[8];
	FColor colors[8];

	float GetProgressFill();

	void FillHorizontalProgressBar(FRect rect);

	void FillVerticalProgressBar(FRect rect);

	void FillColors();

	void RenderProgressBar();
};