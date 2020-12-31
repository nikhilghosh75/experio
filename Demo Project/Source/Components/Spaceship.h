#pragma once
#include "Runtime/Framework/Framework.h"

class Spaceship : public Component
{
private:
	bool isActive = false;
	bool isAccelerating = false;

public:
	SETUP_COMPONENT(Spaceship);

	float acceleration;
	float topSpeed;

	virtual void Start() override;

	virtual void Update() override;

	static float CalculateAcceleration(float power, float currentFuel);
};