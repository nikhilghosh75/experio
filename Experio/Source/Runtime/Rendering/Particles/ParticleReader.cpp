#include "ParticleReader.h"
#include "../../Containers/LString.h"

namespace Experio::Experimental
{
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
}

void ParticleReader::ParseColorOverLife(XMLTreeNode * node, ParticleSystem & system)
{
}

}
