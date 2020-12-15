#include "XMLReader.h"
#include <fstream>
#include "../LFileOperations.h"
#include "../../Containers/LString.h"

void XMLReader::AddCallback(std::string nodeType, std::function<void(const XMLNode&)> callback)
{
	callbacks.Insert(nodeType, callback);
}

void XMLReader::ClearCallbacks()
{
	callbacks.Empty();
}

uint32_t XMLReader::NumCallbacks()
{
	return callbacks.GetSize();
}

XMLTree XMLReader::ReadFile(const std::string & filepath)
{
	std::ifstream inFile(filepath);
	FileBuffer buffer = LFileOperations::ReadTrimmedFileToBuffer(inFile);

	std::vector<FVector2Int> delimiters = GetDelimiters(buffer);
	std::vector<FVector2Int> tagScopes = GetTagScopes(buffer, delimiters);

	return GenerateTree(buffer, delimiters, tagScopes);
}

std::vector<FVector2Int> XMLReader::GetDelimiters(const FileBuffer & buffer)
{
	int lastDelimiter = 0;
	std::vector<FVector2Int> delimiters;

	for (int i = 0; i < buffer.Size(); i++)
	{
		if (buffer[i] == '<')
		{
			lastDelimiter = i;
		}
		else if (buffer[i] == '>')
		{
			delimiters.emplace_back(lastDelimiter, i);
		}
	}
	return delimiters;
}

std::vector<FVector2Int> XMLReader::GetTagScopes(const FileBuffer& buffer, const std::vector<FVector2Int>& delimiters)
{
	std::vector<FVector2Int> tagScopes;
	tagScopes.reserve(delimiters.size() / 2 + 1);

	for (size_t i = 0; i < delimiters.size(); i++)
	{
		if (buffer[delimiters[i].x + 1] == '/') continue;

		std::string name = buffer.Substr(delimiters[i].x + 1, delimiters[i].y);
		if (LString::HasChar(name, ' '))
		{
			name = name.substr(0, LString::FindFirstOfChar(name, ' '));
		}

		for (size_t j = i + 1; j < delimiters.size(); j++)
		{
			if (buffer[delimiters[j].x + 1] != '/') continue;

			std::string foundName = buffer.Substr(delimiters[j].x + 2, delimiters[j].y);
			if (foundName == name)
			{
				tagScopes.emplace_back(i, j);
				break;
			}
		}
	}
	return tagScopes;
}

XMLTree XMLReader::GenerateTree(const FileBuffer & buffer, const std::vector<FVector2Int>& delimiters, const std::vector<FVector2Int>& tags)
{
	XMLTree tree;

	if (tags[0].x == 0 && tags[0].y == delimiters.size() - 1)
	{
		tree.CreateRoot(ParseNode(buffer, delimiters[tags[0].x].x, delimiters[tags[0].y].y));
	}
	else
	{
		tree.EmplaceRoot();
	}

	TTypedTreeNode<XMLNode>* current = tree.GetRoot();
	FVector2Int currentTag = tags[0];
	for (size_t i = 1; i < tags.size(); i++)
	{
		if (!Within(tags[i], currentTag))
		{
			current = current->parentNode;
		}

		current->AddChild(ParseNode(buffer, delimiters[tags[i].x].x, delimiters[tags[i].y].y));
		current = current->children[current->children.size() - 1];
		currentTag = tags[i];
	}

	return tree;
}

XMLNode XMLReader::ParseNode(const FileBuffer& buffer, int start, int end)
{
	std::string nodeString = buffer.Substr(start, end);
	size_t indexOfGreaterThan = LString::FindFirstOfChar(nodeString, '>');
	size_t indexOfSpace = LString::FindFirstOfChar(nodeString, ' ');

	XMLNode node;
	if (indexOfSpace > indexOfGreaterThan)
	{
		node.nodeType = nodeString.substr(1, indexOfGreaterThan - 1);
	}
	else
	{
		node.nodeType = nodeString.substr(1, indexOfSpace - 1);
		size_t lastSpace = indexOfSpace;
		for (size_t i = indexOfSpace + 1; i < indexOfGreaterThan; i++)
		{
			if (nodeString[i] == '"')
			{
				i++;
				while (nodeString[i] != '"')
				{
					i++;
				}
			}
			else if (nodeString[i] == ' ')
			{
				node.modifiers.push_back(ParseModifier(buffer, lastSpace + start, i + start));
				lastSpace = i;
			}
		}
		node.modifiers.push_back(ParseModifier(buffer, lastSpace + start, indexOfGreaterThan + start));
	}

	size_t indexOfLessThan;
	for (size_t i = indexOfGreaterThan; i < end; i++)
	{
		if (nodeString[i] == '<')
		{
			indexOfLessThan = i; break;
		}
	}
	node.content = nodeString.substr(indexOfGreaterThan + 1, indexOfLessThan - indexOfGreaterThan - 1);

	std::function<void(const XMLNode&)> callback;
	if (callbacks.SafeGet(node.nodeType, callback))
	{
		callback(node);
	}

	return node;
}

XMLModifier XMLReader::ParseModifier(const FileBuffer & buffer, int start, int end)
{
	XMLModifier modifier;

	std::string modifierString = buffer.Substr(start, end);
	size_t equalIndex = LString::FindFirstOfChar(modifierString, '=');
	modifier.name = modifierString.substr(0, equalIndex);
	modifier.content = modifierString.substr(equalIndex + 1);

	return modifier;
}

bool XMLReader::Within(const FVector2Int & v1, const FVector2Int & v2) const
{
	return v1.x > v2.x && v1.y < v2.y;
}

