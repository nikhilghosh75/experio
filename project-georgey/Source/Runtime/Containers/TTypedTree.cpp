#include "TTypedTree.h"
#include <string>
#include "../Debug/TempProfiler.h"

void TTypedTreeTest()
{
	TempProfiler profiler("Typed Tree Test");

	TTypedTree<std::string> typedTree("Animal");
	typedTree.AddChildToRoot("Mammal");
	typedTree.AddChildToRoot("Amphibian");
	
	TTypedTreeNode<std::string>* mammal = typedTree.GetRoot()->children[0];
	mammal->AddChild("Carnivore");
	mammal->AddChild("Edentata");
	mammal->AddChild("Insectivora");
	mammal->AddChild("Primate");

	TTypedTreeNode<std::string>* amphibian = typedTree.GetRoot()->children[1];
	amphibian->AddChild("Frog");
	amphibian->AddChild("Earthworm");
	amphibian->AddChild("Salamander");

	TTypedTreeNode<std::string>* primate = mammal->children[3];
	primate->AddChild("Human");
	primate->AddChild("Ape");
	primate->AddChild("Monkey");
	
	TTypedTreeNode<std::string>* insect = mammal->children[2];
	insect->AddChild("Cockroaches");
	insect->AddChild("Beetles");
	insect->AddChild("Mosquito");
	insect->AddChild("Flies");
	insect->AddChild("Bee");
	insect->AddChild("Termites");
	insect->AddChild("Dragonflies");
	insect->AddChild("Crickets");

	TTypedTreeIterator<string> typedTreeIterator(&typedTree);

	for (int i = 0; i < typedTree.GetCount(); i++)
	{
		typedTreeIterator.Increment();
	}

	mammal->DeleteChild(1);
}

/*
	TTypedTreeIterator
*/

template<class T>
TTypedTreeIterator<T>::TTypedTreeIterator(TTypedTree<T>* tree)
{
	this->container = tree;
	this->current = tree->GetRoot();
	this->nodeVisitedCount = 1;
	this->currentDepth = 0;

	for (int i = 0; i < MAX_TYPED_TREE_DEPTH; i++) { this->position[i] = 0; }
}

template<class T>
bool TTypedTreeIterator<T>::IsAtEnd()
{
	return this->nodeVisitedCount >= this->container->GetCount();
}

template<class T>
void TTypedTreeIterator<T>::Increment()
{
	// First Element
	if (this->nodeVisitedCount == 1)
	{
		this->current = this->current->children[0];
		this->nodeVisitedCount++;
	}
	// If it has children
	else if (this->current->children.size() > 0)
	{
		this->current = this->current->children[0];
		currentDepth++;
		position[currentDepth] = 0;
		this->nodeVisitedCount++;
	}
	else
	{
		TTypedTreeNode<T>* tempCurrent = this->current;
		for (int i = this->currentDepth; i > 0; i--)
		{
			tempCurrent = tempCurrent->parentNode;
			if (tempCurrent->children.size() > position[i] + 1)
			{
				this->current = tempCurrent->children[position[i] + 1];
				position[i]++;
				this->nodeVisitedCount++;
				return;
			}
		}
		this->current = tempCurrent->children[(position[0] + 1) % tempCurrent->children.size()];
		currentDepth = 0;
		this->nodeVisitedCount++;
	}
}
