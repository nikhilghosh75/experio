#include "ParticleSaver.h"
#include "Runtime/Math/LMath.h"

#define PB_PARTICLE_TIMESTEP 0.02f

void ParticleSaver::SaveParticleSystem(const ParticleSystem& particleSystem, const std::string& filepath)
{
}

unsigned int ParticleSaver::GetMaxCount(const ParticleSystem& particleSystem)
{
    unsigned int numTimesteps = particleSystem.playbackTime / PB_PARTICLE_TIMESTEP;
    unsigned int lifeSteps = particleSystem.defaultLifetime / PB_PARTICLE_TIMESTEP;

    // Runs a simulation of the particle counts to determine the amount of particles spawned over time
    std::vector<float> particlesSpawned = GetParticlesSpawnedPerTimestep(particleSystem);
    
    float currentNumParticles = particlesSpawned[0];
    float maxNumParticles = currentNumParticles;
    for (unsigned int i = 1; i < numTimesteps; i++)
    {
        currentNumParticles += particlesSpawned[i];
        if (i >= lifeSteps)
        {
            currentNumParticles -= particlesSpawned[i - lifeSteps];
        }

        maxNumParticles = currentNumParticles > maxNumParticles ? currentNumParticles : maxNumParticles;
    }

    return maxNumParticles;
}

std::vector<float> ParticleSaver::GetParticlesSpawnedPerTimestep(const ParticleSystem& particleSystem)
{
    unsigned int numTimesteps = particleSystem.playbackTime / PB_PARTICLE_TIMESTEP;

    std::vector<float> particlesSpawnedPerTimestep;
    particlesSpawnedPerTimestep.reserve(numTimesteps);

    particlesSpawnedPerTimestep.push_back(GetInitialParticles(particleSystem));

    for (unsigned int i = 1; i < numTimesteps; i++)
    {
        particlesSpawnedPerTimestep.push_back(GetNumSpawnedAt(particleSystem, i * PB_PARTICLE_TIMESTEP));
    }

    return particlesSpawnedPerTimestep;
}

float ParticleSaver::GetInitialParticles(const ParticleSystem& particleSystem)
{
    const SpawnAtStart* spawnAtStart = particleSystem.FindStartParticleModifier<SpawnAtStart>();
    if (spawnAtStart != nullptr)
        return spawnAtStart->numToSpawn;
    return 0.0f;
}

float ParticleSaver::GetNumSpawnedAt(const ParticleSystem& particleSystem, float time)
{
    return (float)particleSystem.spawnModifier.ParticlesToSpawn(time, PB_PARTICLE_TIMESTEP);
}
