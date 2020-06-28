#include "FColor.h"

const FColor FColor::Black(0.f, 0.f, 0.f);
const FColor FColor::Charcoal(52, 40, 44);
const FColor FColor::Gunmetal(44, 53, 57);
const FColor FColor::Midnight(43, 27, 23);
const FColor FColor::Night(12, 9, 10);
const FColor FColor::Red(1.f, 0.f, 0.f);
const FColor FColor::White(1.f, 1.f, 1.f);

FColor::FColor()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

FColor::FColor(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1;
}

FColor::FColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

FColor::FColor(int r, int g, int b, int a)
{
	this->r = (float)r / 255;
	this->g = (float)g / 255;
	this->b = (float)b / 255;
	this->a = (float)a / 255;
}

FColor FColor::RandomColor(bool randomAlpha)
{
	return FColor(
		(rand() % 256) / 256.f,
		(rand() % 256) / 256.f,
		(rand() % 256) / 256.f,
		randomAlpha ? (rand() % 256) / 256.f : 1.f
	);
}
