#pragma once

#include "../Framework/Framework.h"
#include "../Math/FColor.h"
#include "../Rendering/Managers/TextureManager.h"

class Panel : public Component
{
public:
	Panel();
	Panel(GameObject* gameObject);

	float roundedPixels;
	FColor color;
	TextureRef texture;

	virtual void Start() override;

	virtual void Update() override;

	void RenderPanel();

private:
	Shader* shader;

	bool wasTexturedLastFrame;

	void RenderColored();
	
	void RenderTextured();

	float GetCornerPoint();
};