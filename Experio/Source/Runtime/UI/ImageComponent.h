#pragma once
#include "../Rendering/Managers/TextureManager.h"
#include "../Framework/Framework.h"
#include "../Math/FColor.h"

class ImageComponent : public Component
{
	static const FRect imageUVRect;

public:
	ImageComponent();
	ImageComponent(GameObject* gameObject);

	TextureRef texture;
	FColor tint;

	virtual void Start() override;

	virtual void Update() override;

private:
	Shader* shader;
};