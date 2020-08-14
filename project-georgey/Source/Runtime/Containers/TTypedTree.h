#pragma once
#include "Iterator.h"
#include <vector>

#define TYPED_TREE_START_CAPACITY 4
#define TYPED_TREE_ADD_CAPACITY 8
#define MAX_TYPED_TREE_DEPTH 32

template <class T>
class TTypedTree;

// TTypedTreeNode

template<class T>
struct TTypedTreeNode
{
	TTypedTreeNode()
	{
		object = T();
		parentNode = nullptr;
		children = std::vector<TTypedTreeNode<T>*>();
		this->owningTree = nullptr;
	}

	TTypedTreeNode(T newObject)
	{
		object = newObject;
		parentNode = nullptr;
		children = std::vector<TTypedTreeNode<T>*>();
		owningTree = nullptr;
	}

	TTypedTreeNode(T newObject, TTypedTree<T>* owningTree)
	{
		object = newObject;
		parentNode = nullptr;
		children = std::vector<TTypedTreeNode<T>*>();
		this->owningTree = owningTree;
	}

	T object;
	TTypedTreeNode<T>* parentNode;
	std::vector<TTypedTreeNode<T>*> children;
	TTypedTree<T>* owningTree;
	uint8_t depth;

	bool IsRoot() const { return !IsChild(); }
	bool IsParent() const { return this->childrenCount != 0; }
	bool IsChild() const { return this->parentNode != nullptr; }

	TTypedTreeNode<T>& AddChild(T newObject)
	{
		children.push_back(new TTypedTreeNode<T>(newObject, owningTree));
		children[children.size() - 1]->parentNode = this;
		this->owningTree->NodeAdded();
		return *children[children.size() - 1];
	}

	template<typename ... Args>
	TTypedTreeNode<T>& EmplaceChild(Args&& ... args)
	{
		children.push_back(new TTypedTreeNode<T>(T(std::forward<Args>(args)), owningTree));
		children[children.size() - 1]->parentNode = this;
		this->owningTree->NodeAdded();
		return *children[children.size() - 1];
	}

	void DeleteChild(int index)
	{
		for (int i = index + 1; i < children.size(); i++)
		{
			children[i - 1] = children[i];
		}
		children.pop_back();
		this->owningTree->NodeDeleted();
	}
};

// TTypedTree

template <class T>
class TTypedTree
{
	unsigned int count;
	uint8_t maxDepth = 1;
	TTypedTreeNode<T>* root;
public:

	TTypedTree()
	{
		this->root = nullptr;
		this->count = 0;
	}

	TTypedTree(T root)
	{
		this->root = new TTypedTreeNode<T>(root);
		this->root->owningTree = this;
		this->count = 1;
	}

	void NodeAdded() { this->count++; }
	void NodeDeleted() { this->count--; }

	void Empty() { static_assert(false); }

	unsigned int GetCount() const { return count; }
	TTypedTreeNode<T>* GetRoot() const { return root; }
	T& GetRootObject() const { return root->object; }

	void AddChildToRoot(T item)
	{
		this->root->AddChild(item);
	}
};

// TTypedTreeIterator

template <class T>
class TTypedTreeIterator
{
public:
	TTypedTree<T>* container;
	TTypedTreeNode<T>* current;

private:
	unsigned int nodeVisitedCount = 1;
	int currentDepth;
	bool goDown = false;

	uint8_t position[MAX_TYPED_TREE_DEPTH];
public:
	TTypedTreeIterator(TTypedTree<T>* tree);

	bool IsAtEnd();
	void Increment();
};

void TTypedTreeTest();
