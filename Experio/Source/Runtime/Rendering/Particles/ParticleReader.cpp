#include "ParticleReader.h"
#include "../../Containers/LString.h"
#include "../../Debug/Debug.h"

ParticleSystem ParticleReader::ReadParticleSystem(const std::string & filepath)
{
	XMLReader reader;
	ParticleSystem system;

	reader.AddCallback("Name", [&system](const XMLNode& node) { system.name = node.content; });
	reader.AddCallback("MaxCount", [&system](const XMLNode& node) { system.maxCount = LString::StringToUInt(node.content); });

	XMLTree particleTree = reader.ReadFile(filepath);
	XMLTreeNode* modifiersNode = particleTree.GetRoot()->children[1];

	for (size_t i = 0; i < modifiersNode->children.size(); i++)
	{
		XMLTreeNode* currentNode = modifiersNode->children[i];
		if (currentNode->object.nodeType == "SizeOverLife")
			ParseSizeOverLife(currentNode, system);
		else if (currentNode->object.nodeType == "ColorOverLife")
			ParseColorOverLife(currentNode, system);
	}

	return system;
}

void ParticleReader::ParseSizeOverLife(XMLTreeNode* node, ParticleSystem & system)
{
	if (node->children.size() < 3)
	{
		Debug::LogError("Particle System node \"SizeOverLife\" does not the proper number of nodes");
		return;
	}

	SizeOverLife* sizeOverLife = system.AddParticleModifier<SizeOverLife>();

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

	ColorOverLife* colorOverLife = system.AddParticleModifier<ColorOverLife>();

	XMLTreeNode* redCurveNode = node->children[0];
	XMLTreeNode* greenCurveNode = node->children[1];
	XMLTreeNode* blueCurveNode = node->children[2];

	ParseCurve(redCurveNode, colorOverLife->redCurve);
	ParseCurve(greenCurveNode, colorOverLife->greenCurve);
	ParseCurve(blueCurveNode, colorOverLife->blueCurve);
}

void ParticleReader::ParseCurve(XMLTreeNode* node, Bezier& bezier)
{
	if (node->object.nodeType != "Curve")
	{
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
	float startX = LString::StringToFloat(node1.modifiers[0].content);
	float startY = LString::StringToFloat(node1.modifiers[1].content);

	float endX = LString::StringToFloat(node2.modifiers[0].content);
	float endY = LString::StringToFloat(node2.modifiers[1].content);
	bezier.Insert(startX, startY, endX, endY);
}

