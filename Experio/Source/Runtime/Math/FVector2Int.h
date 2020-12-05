#pragma once

struct FVector2Int
{
	int x, y;

	FVector2Int();
	FVector2Int(int x, int y);

	float Magnitude() const;
	int SqrMagnitude() const;
};