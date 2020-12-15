#pragma once
#include <string>

namespace Experio::Experimental
{

class ParticleSystem
{
public:
	std::string name;
	uint32_t maxCount;
};

class ParticleReader
{
public:
	static ParticleSystem ReadParticleSystem(const std::string& filepath);
};

}