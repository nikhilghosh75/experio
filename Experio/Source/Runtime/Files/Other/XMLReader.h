#pragma once
#include "../FileBuffer.h"
#include "../../Containers/THashtable.h"
#include "../../Containers/TPair.h"
#include "../../Containers/TTypedTree.h"
#include "../../Math/FVector2Int.h"
#include <string>
#include <vector>

struct XMLModifier
{
	std::string name;
	std::string content;
};

struct XMLNode
{
	std::string nodeType;
	std::vector<XMLModifier> modifiers;
	std::string content;

	XMLNode()
	{
		this->nodeType = "";
		this->content = "";
	}
};

using XMLTree = TTypedTree<XMLNode>;
using XMLTreeNode = TTypedTreeNode<XMLNode>;

class XMLReader
{
	THashtable<std::string, std::function<void(const XMLNode&)>, StringHashFunction> callbacks;
public:
	void AddCallback(std::string nodeType, std::function<void(const XMLNode&)> callback);

	void ClearCallbacks();

	uint32_t NumCallbacks();

	XMLTree ReadFile(const std::string& filepath);

private:
	std::vector<FVector2Int> GetDelimiters(const FileBuffer& buffer);

	std::vector<FVector2Int> GetTagScopes(const FileBuffer& buffer, const std::vector<FVector2Int>& delimiters);

	XMLTree GenerateTree(const FileBuffer& buffer, const std::vector<FVector2Int>& delimiters, const std::vector<FVector2Int>& tags);

	XMLNode ParseNode(const FileBuffer& buffer, int start, int end);

	XMLModifier ParseModifier(const FileBuffer& buffer, int start, int end);

	// Is V1 within V2
	// Note that this function did not make sense to put in the FVector2Int class, as they may not always represent a range
	bool Within(const FVector2Int& v1, const FVector2Int& v2) const;
};
