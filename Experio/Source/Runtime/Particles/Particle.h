#pragma once
#include "../Math/FColor.h"
#include "../Math/FVector3.h"

struct FParticleData
{
	FVector3 position;
	FVector3 speed;
	FColor color;
	float life;

	FParticleData()
	{
		position = FVector3(0, 0, 0);
		speed = FVector3(0, 0, 0);
		color = FColor();
		life = -1.0f;
	}
};