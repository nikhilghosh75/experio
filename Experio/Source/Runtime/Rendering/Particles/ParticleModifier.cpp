#include "ParticleModifier.h"
#include "ParticleComponent.h"
#include "../../Math/LMath.h"

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

// Spawn Modifier

SpawnModifier::SpawnModifier()
{
	mode = ESpawnMode::None;
}

SpawnModifier::SpawnModifier(ESpawnMode newMode)
{
	this->mode = newMode;
}

SpawnModifier::~SpawnModifier()
{
}

void SpawnModifier::SetMode(ESpawnMode newMode)
{
	mode = newMode;
	switch (mode)
	{
	case ESpawnMode::Burst:
		burstSpawnInfo.currentTime = 0;
		break;
	}
}

void SpawnModifier::Update(ParticleComponent& component)
{
	unsigned int numParticlesToSpawn = ParticlesToSpawn(component.GetParticleTime(), GameTime::deltaTime);
	component.SpawnParticles(numParticlesToSpawn);
}

unsigned int SpawnModifier::ParticlesToSpawn(float time, float deltaTime) const
{
	switch (mode)
	{
	case ESpawnMode::Burst: ParticlesToSpawnBurst(time, deltaTime);
	case ESpawnMode::OverLife: ParticlesToSpawnOverLife(time, deltaTime);
	}
	return 0;
}

unsigned int SpawnModifier::ParticlesToSpawnBurst(float time, float deltaTime) const
{
	size_t currentTime = 0;
	for (size_t i = 0; i < burstSpawnInfo.times.size(); i++)
	{
		if (time < burstSpawnInfo.times[i].time)
		{
			currentTime = i;
			break;
		}
	}

	float nextBurstTime = burstSpawnInfo.times[currentTime].time;
	if (LMath::Abs(nextBurstTime - time) < deltaTime)
	{
		return burstSpawnInfo.times[currentTime].num;
	}
	return 0;
}

unsigned int SpawnModifier::ParticlesToSpawnOverLife(float time, float deltaTime) const
{
	return spawnCurve.Get(time) * GameTime::deltaTime;
}

