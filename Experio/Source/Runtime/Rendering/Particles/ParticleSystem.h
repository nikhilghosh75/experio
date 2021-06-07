#pragma once
#include <vector>
#include <string>
#include "ParticleModifier.h"

class ParticleSystem
{
public:
	std::string name;
	uint32_t maxCount;
	float defaultLifetime; // For individual particles
	float playbackTime; // Time of entire system

	ParticleSystem();
	ParticleSystem(const ParticleSystem& particleSystem);

	ParticleSystem& operator=(const ParticleSystem& particleSystem);

	size_t SizeOf() const;

	SpawnModifier spawnModifier;

	std::vector<StartParticleModifier*> startModifiers;
	std::vector<ParticleModifier*> modifiers;

	void Start(ParticleComponent& component);

	void Update(ParticleComponent& component);

	template<typename T>
	const T* FindParticleModifier() const
	{
		for (size_t i = 0; i < modifiers.size(); i++)
		{
			if (dynamic_cast<T*>(modifiers[i]) != nullptr)
				return dynamic_cast<T*>(modifiers[i]);
		}
		return nullptr;
	}

	template<typename T>
	const T* FindStartParticleModifier() const
	{
		for (size_t i = 0; i < startModifiers.size(); i++)
		{
			if (dynamic_cast<T*>(startModifiers[i]) != nullptr)
				return dynamic_cast<T*>(startModifiers[i]);
		}
		return nullptr;
	}
};