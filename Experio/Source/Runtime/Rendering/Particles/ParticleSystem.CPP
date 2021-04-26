#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::ParticleSystem(const ParticleSystem& particleSystem)
{
    this->name = particleSystem.name;
    this->maxCount = particleSystem.maxCount;
    this->defaultLifetime = particleSystem.defaultLifetime;
    this->modifiers = particleSystem.modifiers;
    this->startModifiers = particleSystem.startModifiers;

    this->spawnModifier.mode = particleSystem.spawnModifier.mode;
    switch (spawnModifier.mode)
    {
    case ESpawnMode::Burst:
        this->spawnModifier.burstSpawnInfo = particleSystem.spawnModifier.burstSpawnInfo; break;
    case ESpawnMode::OverLife:
        this->spawnModifier.spawnCurve = particleSystem.spawnModifier.spawnCurve; break;
    }
}

size_t ParticleSystem::SizeOf() const
{
    return sizeof(FParticleData) * maxCount;
}

void ParticleSystem::Start(ParticleComponent& component)
{
    for (size_t i = 0; i < startModifiers.size(); i++)
    {
        startModifiers[i]->OnStart(component);
    }
}
