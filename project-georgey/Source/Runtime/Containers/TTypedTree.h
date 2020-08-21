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
		this->root = new TTypedTreeNode<T>(root, this);
		this->count = 1;
	}

	void NodeAdded() { this->count++; }
	void NodeDeleted() { this->count--; }

	void Empty() { static_assert(false); }

	unsigned int GetCount() const { return count; }
	TTypedTreeNode<T>* GetRoot() const { return root; }
	T& GetRootObject() const { return root->object; }
	void SetCount(unsigned int newCount) 
	{
		#pragma message("Only use this if you know what you're doing")
		count = newCount;
	}

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
	TTypedTreeIterator(TTypedTree<T>* tree)
	{
		this->container = tree;
		this->current = tree->GetRoot();
		this->nodeVisitedCount = 1;
		this->currentDepth = 0;

		for (int i = 0; i < MAX_TYPED_TREE_DEPTH; i++) { this->position[i] = 0; }
	}

	bool IsAtEnd() const { return this->nodeVisitedCount >= this->container->GetCount(); }

	void Increment()
	{
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
			if (position[0] + 1 >= tempCurrent->children.size())
			{
				return;
			}
			this->current = tempCurrent->children[(position[0] + 1) % tempCurrent->children.size()];
			currentDepth = 0;
			this->nodeVisitedCount++;
		}
	}
};

void TTypedTreeTest();

/*
template<class T>
void CalculateCount(TTypedTree<T>* tree)
{
	int count = 0;
	TTypedTreeIterator<T> iterator(tree);

	while (!iterator.SlowIsAtEnd())
	{
		iterator.Increment();
		count++;
	}

	tree->SetCount(count);
}
*/