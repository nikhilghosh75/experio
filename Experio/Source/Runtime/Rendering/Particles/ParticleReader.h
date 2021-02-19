#pragma once
#include <string>
#include "../../Files/Other/XMLReader.h"
#include "ParticleModifier.h"

namespace Experio::Experimental
{

class ParticleSystem
{
public:
	std::string name;
	uint32_t maxCount;

	std::vector<ParticleModifier*> modifiers;
};

class ParticleReader
{
public:
	static ParticleSystem ReadParticleSystem(const std::string& filepath);

	static void ParseSizeOverLife(XMLTreeNode* node, ParticleSystem& system);

	static void ParseColorOverLife(XMLTreeNode* node, ParticleSystem& system);
};

}