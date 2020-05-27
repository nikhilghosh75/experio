#pragma once
#include "FVector3.h"

struct FVector2
{
	float x;
	float y;

	FVector2();
	FVector2(float x, float y);
	//FVector2(FVector3 V);

	static bool IsEqual(FVector2 a, FVector2 b);

	bool operator==(const FVector2 Other) const;
};