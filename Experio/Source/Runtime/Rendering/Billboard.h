#pragma once

#include "Texture.h"
#include "../Math/FVector2.h"
#include "../Math/FVector3.h"
#include "../Framework/Framework.h"

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
	Texture* billboardTexture;
	EBillboardSizeType sizeType;
	EBilboardOrientation orientation;
	FVector2 billboardSize;

	union
	{
		FVector3 rotationAxis;
		FVector3 eulerRotation;
	};

	Billboard(GameObject* object);

	virtual void Start() override;
	virtual void Update() override;
};