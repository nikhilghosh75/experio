#pragma once
#include "../Rendering/Managers/TextureManager.h"
#include "../Framework/Framework.h"

class ImageComponent : public Component
{
	static const FRect imageUVRect;

public:
	ImageComponent();
	ImageComponent(GameObject* gameObject);

	TextureRef texture;

	virtual void Start() override;

	virtual void Update() override;
};