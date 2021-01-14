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

class ColorOverLife: ParticleModifier
{
public:
	FCurve redCurve;
	FCurve greenCurve;
	FCurve blueCurve;

	virtual void Update(FParticleData& particle) override
	{
		particle.color = FColor(redCurve.GetY(particle.life), greenCurve.GetY(particle.life), 
			blueCurve.GetY(particle.life));
	}
};

class VelocityOverLife : ParticleModifier
{
	FCurve speedXCurve;
	FCurve speedYCurve;
	FCurve speedZCurve;

	virtual void Update(FParticleData& particle) override
	{
		particle.speed = FVector3(speedXCurve.GetY(particle.life), speedYCurve.GetY(particle.life),
			speedZCurve.GetY(particle.life));
	}
};