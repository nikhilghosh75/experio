#pragma once
#include <string>
#include "../../Files/Other/XMLReader.h"
#include "ParticleModifier.h"
#include "ParticleSystem.h"

class ParticleReader
{
public:
	static ParticleSystem ReadParticleSystem(const std::string& filepath);

private:

	static void ParseSizeOverLife(XMLTreeNode* node, ParticleSystem& system);

	static void ParseColorOverLife(XMLTreeNode* node, ParticleSystem& system);

	static void ParseCurve(XMLTreeNode* node, Bezier& bezier);
	static void ParseCurvePoint(XMLNode& node1, XMLNode& node2, Bezier& bezier);
};
