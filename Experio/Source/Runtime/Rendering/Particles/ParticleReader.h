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
	static void ParseNode(XMLTreeNode* node, ParticleSystem& system);

	static void ParseSizeOverLife(XMLTreeNode* node, ParticleSystem& system);

	static void ParseColorOverLife(XMLTreeNode* node, ParticleSystem& system);

	static void ParseVelocityOverLife(XMLTreeNode* node, ParticleSystem& system);

	static void ParseGravityOverLife(XMLTreeNode* node, ParticleSystem& system);

	static void ParseSpawnAtStart(XMLTreeNode* node, ParticleSystem& system);

	static void ParseSpawn(XMLTreeNode* node, ParticleSystem& system);

	static void ParseBurstSpawnInfo(XMLTreeNode* node, FBurstSpawnInfo& burstSpawn);

	static FBurstPoint ParseBurstPoint(const std::string& str);

	static void ParseCurve(XMLTreeNode* node, Bezier& bezier);
	static void ParseCurvePoint(XMLNode& node1, XMLNode& node2, Bezier& bezier);

	static ESpawnMode StringToMode(const std::string& str);
};
