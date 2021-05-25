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
	switch (mode)
	{
	case ESpawnMode::OverLife: UpdateSpawnOverLife(component); break;
	case ESpawnMode::Burst: UpdateBurst(component); break;
	}
}

void SpawnModifier::UpdateSpawnOverLife(ParticleComponent& component)
{
	unsigned int particlesToSpawn = spawnCurve.Get(component.GetParticleTime()) * GameTime::deltaTime;
	component.SpawnParticles(particlesToSpawn);
}

void SpawnModifier::UpdateBurst(ParticleComponent& component)
{
	if (burstSpawnInfo.currentTime == burstSpawnInfo.times.size())
	{
		burstSpawnInfo.currentTime = 0;
	}

	float nextBurstTime = burstSpawnInfo.times[burstSpawnInfo.currentTime].time;
	if (component.GetParticleTime() < nextBurstTime)
	{
		unsigned int particlesToSpawn = burstSpawnInfo.times[burstSpawnInfo.currentTime].num;
		component.SpawnParticles(particlesToSpawn);

		burstSpawnInfo.currentTime++;
	}
}

