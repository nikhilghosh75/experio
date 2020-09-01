#pragma once
#include "../Math/FVector3.h"
#include "../Math/FQuaternion.h"
#include "../Math/FColor.h"

enum class ELightType : uint8_t
{
	Spotlight,
	Directional
};

struct FLightData
{
	FVector3 worldPosition;
	FQuaternion worldRotation;
	FColor color;
	float power;
	ELightType lightType;

	FLightData()
	{
		this->worldPosition = FVector3();
		this->worldRotation = FQuaternion();
		this->color = FColor::White;
		this->power = 1;
		this->lightType = ELightType::Spotlight;
	}

	FLightData(FVector3 position, FQuaternion rotation, FColor color, float power)
	{
		this->worldPosition = position;
		this->worldRotation = rotation;
		this->color = color;
		this->power = power;
		this->lightType = ELightType::Spotlight;
	}
};