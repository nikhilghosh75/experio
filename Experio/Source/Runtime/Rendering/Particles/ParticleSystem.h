#pragma once
#include <vector>
#include <string>

class ParticleSystem
{
public:
	std::string name;
	uint32_t maxCount;

	std::vector<ParticleModifier*> modifiers;

	template<typename T>
	T* AddParticleModifier()
	{
		modifiers.push_back(new T());
		return modifiers.back();
	}
};