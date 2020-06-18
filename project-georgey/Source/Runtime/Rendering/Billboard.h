#pragma once

#include "Texture.h"
#include "../Math/FVector2.h"
#include "../Math/FVector3.h"

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

class Billboard
{
public:
	Texture* billboardTexture;
	EBillboardSizeType sizeType;
	EBilboardOrientation orientation;
	FVector3 billboardPosition;
	FVector2 billboardSize;

	union
	{
		FVector3 rotationAxis;
		FVector3 eulerRotation;
	};

	Billboard();
};