#pragma once
#include <vector>
#include <string>
#include "ParticleModifier.h"

class ParticleSystem
{
public:
	std::string name;
	uint32_t maxCount;
	float defaultLifetime;

	ParticleSystem();
	ParticleSystem(const ParticleSystem& particleSystem);

	ParticleSystem& operator=(const ParticleSystem& particleSystem);

	size_t SizeOf() const;

	SpawnModifier spawnModifier;

	std::vector<StartParticleModifier*> startModifiers;
	std::vector<ParticleModifier*> modifiers;

	void Start(ParticleComponent& component);
};