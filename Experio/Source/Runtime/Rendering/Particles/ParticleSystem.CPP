#include "ParticleSystem.h"
#include "ParticleComponent.h"

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
        this->spawnModifier.burstSpawnInfo.times = particleSystem.spawnModifier.burstSpawnInfo.times; break;
    case ESpawnMode::OverLife:
        this->spawnModifier.spawnCurve = particleSystem.spawnModifier.spawnCurve; break;
    }
}

ParticleSystem& ParticleSystem::operator=(const ParticleSystem& particleSystem)
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

    return *this;
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

void ParticleSystem::Update(ParticleComponent& component)
{
    spawnModifier.Update(component);

    for (size_t i = 0; i < component.maxParticles; i++)
    {
        if (component.particles[i].life > 0.0f)
        {
            for (size_t j = 0; j < modifiers.size(); j++)
            {
                modifiers[i]->Update(component.particles[i]);
            }
        }
    }
}
