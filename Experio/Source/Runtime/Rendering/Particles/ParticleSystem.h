#pragma once
#include <vector>
#include <string>
#include "ParticleModifier.h"

class ParticleSystem
{
public:
	std::string name;
	uint32_t maxCount;

	size_t SizeOf() const;

	std::vector<ParticleModifier*> modifiers;
};