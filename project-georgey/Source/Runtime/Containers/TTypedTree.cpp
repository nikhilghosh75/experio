#include "TTypedTree.h"
#include <string>
#include "../Debug/TempProfiler.h"

#define TYPED_TREE_START_CAPACITY 4
#define TYPED_TREE_ADD_CAPACITY 8

template<class T>
TTypedTreeNode<T>::TTypedTreeNode(T newObject)
{
	object = newObject;
	parentNode = nullptr;
	children = std::vector<TTypedTreeNode<T>*>();
	owningTree = nullptr;
}

template<class T>
TTypedTreeNode<T>::TTypedTreeNode(T newObject, TTypedTree<T>* owningTree)
{
	object = newObject;
	parentNode = nullptr;
	children = std::vector<TTypedTreeNode<T>*>();
	this->owningTree = owningTree;
}

template<class T>
bool TTypedTreeNode<T>::IsRoot() const
{
	return !IsChild();
}

template<class T>
bool TTypedTreeNode<T>::IsParent() const
{
	return this->childrenCount != 0;
}

template<class T>
bool TTypedTreeNode<T>::IsChild() const
{
	return this->parentNode != nullptr;
}

template<class T>
void TTypedTreeNode<T>::AddChild(T newObject)
{
	children.push_back(new TTypedTreeNode<T>(newObject, owningTree));
	children[children.size() - 1]->parentNode = this;
	this->owningTree->NodeAdded();
}

template<class T>
void TTypedTreeNode<T>::DeleteChild(int index)
{
	for (int i = index + 1; i < children.size(); i++)
	{
		children[i - 1] = children[i];
	}
	children.pop_back();
	this->owningTree->NodeDeleted();
}

template<class T>
TTypedTree<T>::TTypedTree()
{
	this->root = nullptr;
	this->count = 0;
}

template<class T>
TTypedTree<T>::TTypedTree(T root)
{
	this->root = new TTypedTreeNode<T>(root);
	this->root->owningTree = this;
	this->count = 1;
}

template<class T>
void TTypedTree<T>::NodeAdded()
{
	count++;
}

template<class T>
void TTypedTree<T>::NodeDeleted()
{
	count--;
}

template<class T>
void TTypedTree<T>::Empty()
{
	static_assert(false);
}

template<class T>
void TTypedTree<T>::AddChildToRoot(T item)
{
	this->root->AddChild(item);
}

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

	mammal->DeleteChild(1);
}
