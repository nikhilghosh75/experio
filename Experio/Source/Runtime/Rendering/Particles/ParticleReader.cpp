#include "ParticleReader.h"
#include "../../Containers/LString.h"
#include "../../Debug/Debug.h"

ParticleSystem ParticleReader::ReadParticleSystem(const std::string & filepath)
{
	XMLReader reader;
	ParticleSystem system;

	reader.AddCallback("Name", [&system](const XMLNode& node) { system.name = node.content; });
	reader.AddCallback("MaxCount", [&system](const XMLNode& node) { system.maxCount = LString::StringToUInt(node.content); });
	reader.AddCallback("DefaultLifetime", [&system](const XMLNode& node) {system.defaultLifetime = LString::StringToFloat(node.content); });

	XMLTree particleTree = reader.ReadFile(filepath);
	XMLTreeNode* modifiersNode = particleTree.GetRoot()->children[1];

	ParseSpawn(modifiersNode->children[0], system);
	for (size_t i = 1; i < modifiersNode->children.size(); i++)
	{
		XMLTreeNode* currentNode = modifiersNode->children[i];
		ParseNode(currentNode, system);
	}

	return system;
}

void ParticleReader::ParseNode(XMLTreeNode* node, ParticleSystem& system)
{
	if (node->object.nodeType == "SizeOverLife")
		ParseSizeOverLife(node, system);
	else if (node->object.nodeType == "ColorOverLife")
		ParseColorOverLife(node, system);
	else if (node->object.nodeType == "VelocityOverLife")
		ParseVelocityOverLife(node, system);
	else if (node->object.nodeType == "GravityOverLife")
		ParseGravityOverLife(node, system);
	else if (node->object.nodeType == "SpawnAtStart")
		ParseSpawnAtStart(node, system);
}

void ParticleReader::ParseSizeOverLife(XMLTreeNode* node, ParticleSystem & system)
{
	if (node->children.size() < 3)
	{
		Debug::LogError("Particle System node \"SizeOverLife\" does not the proper number of nodes");
		return;
	}

	system.modifiers.push_back(new SizeOverLife());
	SizeOverLife* sizeOverLife = (SizeOverLife*)system.modifiers.back();

	XMLTreeNode* xCurveNode = node->children[0];
	XMLTreeNode* yCurveNode = node->children[1];
	XMLTreeNode* zCurveNode = node->children[2];

	ParseCurve(xCurveNode, sizeOverLife->sizeXCurve);
	ParseCurve(yCurveNode, sizeOverLife->sizeYCurve);
	ParseCurve(zCurveNode, sizeOverLife->sizeZCurve);
}

void ParticleReader::ParseColorOverLife(XMLTreeNode * node, ParticleSystem & system)
{
	if (node->children.size() < 3)
	{
		Debug::LogError("Particle System node \"SizeOverLife\" does not the proper number of nodes");
		return;
	}

	system.modifiers.push_back(new ColorOverLife());
	ColorOverLife* colorOverLife = (ColorOverLife*)system.modifiers.back();

	XMLTreeNode* redCurveNode = node->children[0];
	XMLTreeNode* greenCurveNode = node->children[1];
	XMLTreeNode* blueCurveNode = node->children[2];

	ParseCurve(redCurveNode, colorOverLife->redCurve);
	ParseCurve(greenCurveNode, colorOverLife->greenCurve);
	ParseCurve(blueCurveNode, colorOverLife->blueCurve);
}

void ParticleReader::ParseVelocityOverLife(XMLTreeNode* node, ParticleSystem& system)
{
	if (node->children.size() < 3)
	{
		Debug::LogError("Particle System node \"VelocityOverLife\" does not the proper number of nodes");
		return;
	}

	system.modifiers.push_back(new VelocityOverLife());
	VelocityOverLife* velocityOverLife = (VelocityOverLife*)system.modifiers.back();

	XMLTreeNode* xCurveNode = node->children[0];
	XMLTreeNode* yCurveNode = node->children[1];
	XMLTreeNode* zCurveNode = node->children[2];

	ParseCurve(xCurveNode, velocityOverLife->speedXCurve);
	ParseCurve(yCurveNode, velocityOverLife->speedYCurve);
	ParseCurve(zCurveNode, velocityOverLife->speedZCurve);
}

void ParticleReader::ParseGravityOverLife(XMLTreeNode* node, ParticleSystem& system)
{
	if (node->children.size() < 1)
	{
		Debug::LogError("Particle System node \"GravityOverLife\" does not the proper number of nodes");
		return;
	}

	system.modifiers.push_back(new GravityOverLife());
	GravityOverLife* gravityOverLife = (GravityOverLife*)system.modifiers.back();

	XMLTreeNode* gravityCurveNode = node->children[0];

	ParseCurve(gravityCurveNode, gravityOverLife->gravityCurve);
}

void ParticleReader::ParseSpawnAtStart(XMLTreeNode* node, ParticleSystem& system)
{
	if (node->children.size() < 1)
	{
		Debug::LogError("Particle System node \"SpawnAtStart\" does not the proper number of modifiers");
		return;
	}

	system.startModifiers.push_back(new SpawnAtStart());
	SpawnAtStart* spawnAtStart = (SpawnAtStart*)system.startModifiers.back();

	spawnAtStart->numToSpawn = LString::StringToUInt(node->object.modifiers[0].content);
}

void ParticleReader::ParseSpawn(XMLTreeNode* node, ParticleSystem& system)
{
	if (node->children.size() < 1)
	{
		Debug::LogError("Particle System node \"Spawn\" does not the proper number of modifiers");
		return;
	}

	system.spawnModifier.mode = StringToMode(node->children[0]->object.content);
	
	switch (system.spawnModifier.mode)
	{
	case ESpawnMode::OverLife:
		ParseCurve(node->children[1], system.spawnModifier.spawnCurve); break;
	case ESpawnMode::Burst:
		ParseBurstSpawnInfo(node->children[1], system.spawnModifier.burstSpawnInfo); break;
	}
}

void ParticleReader::ParseBurstSpawnInfo(XMLTreeNode* node, FBurstSpawnInfo& burstSpawn)
{
	if (node->object.nodeType != "Points")
	{
		Debug::LogError("Burst Spawn Info is not correct");
		return;
	}

	if (node->children.size() == 0)
	{
		Debug::LogError("Burst Spawn Info is empty");
		return;
	}

	for (size_t i = 0; i < node->children.size(); i++)
	{
		FBurstPoint point = ParseBurstPoint(node->children[i]->object.content);
		burstSpawn.times.push_back(point);
	}
}

FBurstPoint ParticleReader::ParseBurstPoint(const std::string& str)
{
	FBurstPoint point;

	size_t commaPosition = LString::FindFirstOfChar(str, ',');
	point.num = LString::SubstrToUInt(str, 1, commaPosition - 1);
	point.time = LString::SubstrToUInt(str, commaPosition, str.size());

	return point;
}

void ParticleReader::ParseCurve(XMLTreeNode* node, Bezier& bezier)
{
	if (node->object.nodeType != "Curve")
	{
		Debug::LogError("Curve is not correct");
		return;
	}

	if (node->children.size() == 0)
	{
		Debug::LogError("Curve is empty");
		return;
	}

	for (size_t i = 0; i < node->children.size() - 1; i++)
	{
		XMLNode& child1 = node->children[i]->object;
		XMLNode& child2 = node->children[i + 1]->object;
		ParseCurvePoint(child1, child2, bezier);
	}
}

void ParticleReader::ParseCurvePoint(XMLNode& node1, XMLNode& node2, Bezier& bezier)
{
	const std::string& startStr = node1.content;
	float startX = LString::SubstrToFloat(startStr, 0, startStr.find(','));
	float startY = LString::SubstrToFloat(startStr, startStr.find(','), startStr.size());

	const std::string& endStr = node2.content;
	float endX = LString::SubstrToFloat(endStr, 0, endStr.find(','));
	float endY = LString::SubstrToFloat(endStr, endStr.find(','), endStr.size());
	bezier.Insert(startX, startY, endX, endY);
}

ESpawnMode ParticleReader::StringToMode(const std::string& str)
{
	if (str == "OverLife") return ESpawnMode::OverLife;
	if (str == "Burst") return ESpawnMode::Burst;

	return ESpawnMode::None;
}

