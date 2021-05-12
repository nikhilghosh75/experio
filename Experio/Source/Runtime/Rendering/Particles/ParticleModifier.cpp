#include "ParticleModifier.h"
#include "ParticleComponent.h"

// Size Over Life

void SizeOverLife::Update(FParticleData& particle)
{
	particle.scale = FVector3(sizeXCurve.Get(particle.life), sizeYCurve.Get(particle.life),
		sizeZCurve.Get(particle.life));
}

// Color Over Life

void ColorOverLife::Update(FParticleData& particle)
{
	particle.color = FColor(redCurve.Get(particle.life), greenCurve.Get(particle.life),
		blueCurve.Get(particle.life));
}

// Velocity Over Life

void VelocityOverLife::Update(FParticleData& particle)
{
	particle.speed = FVector3(speedXCurve.Get(particle.life), speedYCurve.Get(particle.life),
		speedZCurve.Get(particle.life));
}

// Gravity Over Life

void GravityOverLife::Update(FParticleData& particle)
{
	particle.speed.y -= gravityCurve.Get(particle.life);
}

// Spawn At Start

void SpawnAtStart::OnStart(ParticleComponent& component)
{
	component.SpawnParticles(numToSpawn);
}

SpawnModifier::SpawnModifier()
{

}

SpawnModifier::~SpawnModifier()
{

}
