#include "FVector2Int.h"
#include "LMath.h"

FVector2Int::FVector2Int()
{
	this->x = 0;
	this->y = 0;
}

FVector2Int::FVector2Int(int x, int y)
{
	this->x = x;
	this->y = y;
}

float FVector2Int::Magnitude() const
{
	return LMath::Sqrt(this->x * this->x + this->y * this->y);
}

int FVector2Int::SqrMagnitude() const
{
	return this->x * this->x + this->y * this->y;
}
