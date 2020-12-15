#pragma once
#include "Particle.h"
#include "../../Math/FCurve.h"

class ParticleModifier
{
public:
	bool isActive = true;

	virtual void Update(FParticleData& particle) = 0;
};

enum class EParticleModifierType
{
	None = 0,
	SizeOverLife = 10,
	ColorOverLife = 11,
	VelocityOverLife = 12,
	Gravity = 13
};

class SizeOverLife : ParticleModifier
{
public:
	FCurve sizeXCurve;
	FCurve sizeYCurve;
	FCurve sizeZCurve;

	virtual void Update(FParticleData& particle) override
	{
		particle.scale = FVector3(sizeXCurve.GetY(particle.life), sizeYCurve.GetY(particle.life),
			sizeZCurve.GetY(particle.life));
	}
};