#pragma once
#include "Runtime/Rendering/Particles/ParticleSystem.h"

class ParticleSaver
{
public:
	static void SaveParticleSystem(const ParticleSystem& particleSystem, const std::string& filepath);

	static unsigned int GetMaxCount(const ParticleSystem& particleSystem);

private:
	// ---- Calculate Max Count ----
	static std::vector<float> GetParticlesSpawnedPerTimestep(const ParticleSystem& particleSystem);

	static float GetInitialParticles(const ParticleSystem& particleSystem);

	static float GetNumSpawnedAt(const ParticleSystem& particleSystem, float time);
};