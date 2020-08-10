#pragma once
#include "Iterator.h"
#include <vector>

template <class T>
class TTypedTree;

template<class T>
struct TTypedTreeNode
{
	TTypedTreeNode();
	TTypedTreeNode(T newObject);
	TTypedTreeNode(T newObject, TTypedTree<T>* owningTree);

	T object;
	TTypedTreeNode<T>* parentNode;
	std::vector<TTypedTreeNode<T>*> children;
	TTypedTree<T>* owningTree;
	uint8_t depth;

	bool IsRoot() const;
	bool IsParent() const;
	bool IsChild() const;

	T& AddChild(T newObject);
	void DeleteChild(int index);
};

template <class T>
class TTypedTree
{
	unsigned int count;
	uint8_t maxDepth = 1;
	TTypedTreeNode<T>* root;
public:

	TTypedTree();
	TTypedTree(T root);

	void NodeAdded();
	void NodeDeleted();

	void Empty();

	unsigned int GetCount() const { return count; }
	TTypedTreeNode<T>* GetRoot() const { return root; }

	void AddChildToRoot(T item);
};

template <class T>
class TTypedTreeIterator
{
public:
	TTypedTree<T>* container;
	TTypedTreeNode<T>* current;

private:
	unsigned int nodeVisitedCount = 1;
	int currentChild;
	int currentSibling;
	int currentDepth;
	bool goDown = false;

public:
	TTypedTreeIterator(TTypedTree<T>* tree);

	bool IsAtEnd();
	void Increment();
};

void TTypedTreeTest();