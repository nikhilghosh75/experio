#pragma once
#include "Particle.h"
#include "../../Math/Bezier.h"

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

class SizeOverLife : public ParticleModifier
{
public:
	Bezier sizeXCurve;
	Bezier sizeYCurve;
	Bezier sizeZCurve;

	virtual void Update(FParticleData& particle) override
	{
		particle.scale = FVector3(sizeXCurve.Get(particle.life), sizeYCurve.Get(particle.life),
			sizeZCurve.Get(particle.life));
	}
};

class ColorOverLife: public ParticleModifier
{
public:
	Bezier redCurve;
	Bezier greenCurve;
	Bezier blueCurve;

	virtual void Update(FParticleData& particle) override
	{
		particle.color = FColor(redCurve.Get(particle.life), greenCurve.Get(particle.life), 
			blueCurve.Get(particle.life));
	}
};

class VelocityOverLife : public ParticleModifier
{
	Bezier speedXCurve;
	Bezier speedYCurve;
	Bezier speedZCurve;

	virtual void Update(FParticleData& particle) override
	{
		particle.speed = FVector3(speedXCurve.Get(particle.life), speedYCurve.Get(particle.life),
			speedZCurve.Get(particle.life));
	}
};