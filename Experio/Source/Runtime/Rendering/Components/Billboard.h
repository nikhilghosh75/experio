#pragma once

#include "../Texture.h"
#include "../Managers/TextureManager.h"
#include "../../Math/FVector2.h"
#include "../../Math/FVector3.h"
#include "../../Framework/Framework.h"

enum class EBillboardSizeType : uint8_t
{
	World = 10,
	Fixed = 11
};

enum class EBilboardOrientation : uint8_t
{
	Fixed = 48,
	TowardCamera = 49,
	AroundAxis = 50
};

class Billboard : public Component
{
public:
	TextureRef billboardTexture;
	EBillboardSizeType sizeType;
	EBilboardOrientation orientation;
	FVector2 billboardSize;

	Billboard(GameObject* object);

	virtual void Start() override;
	virtual void Update() override;
};