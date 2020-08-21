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