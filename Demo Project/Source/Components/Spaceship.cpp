#include "Spaceship.h"

void Spaceship::Start()
{
}

void Spaceship::Update()
{
}

float Spaceship::CalculateAcceleration(float power, float currentFuel)
{
	if (currentFuel < 20)
		return power * 10;
	return power * 20;
}
