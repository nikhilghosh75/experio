#pragma once
#include "Iterator.h"
#include <vector>
#include <functional>

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

template <class T>
class TTypedTreeIterator;

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

	TTypedTree(const TTypedTree<T>& other)
	{
		this->root = new TTypedTreeNode<T>(other.root->object, this);
		for (int i = 0; i < other.root->children.size(); i++)
		{
			CopyNodeRecursive(other.root->children[i], this->root);
		}
	}

	~TTypedTree()
	{
		DeleteNode(this->root);
	}

	void CreateRoot(T object)
	{
		if (this->root != nullptr)
		{
			delete this->root;
		}

		this->root = new TTypedTreeNode<T>(object, this);
		this->count = 1;
	}

	template<typename ... Args>
	void EmplaceRoot(Args&& ... args)
	{
		if (this->root != nullptr)
		{
			delete this->root;
		}

		this->root = new TTypedTreeNode<T>(T(std::forward<Args>(args)...));
		this->count = 1;
	}

	void NodeAdded() { this->count++; }
	void NodeDeleted() { this->count--; }

	void Empty() 
	{
		if (this->root == nullptr)
		{
			return;
		}
		for (int i = 0; i < this->root->children.size(); i++)
		{
			DeleteNode(this->root->children[i]);
		}
		count = 1;
	}

	unsigned int GetCount() const { return count; }
	TTypedTreeNode<T>* GetRoot() const { return root; }
	T& GetRootObject() const { return root->object; }

	void AddChildToRoot(T item)
	{
		this->root->AddChild(item);
	}

	void CopyNodeRecursive(const TTypedTreeNode<T>* other, TTypedTreeNode<T>* parent)
	{
		TTypedTreeNode<T>* node = new TTypedTreeNode<T>(other->object, this);
		node->parentNode = parent;
		parent->children.push_back(node);
		node->depth = other->depth;
		
		for (int i = 0; i < other->children.size(); i++)
		{
			CopyNodeRecursive(other->children[i], node);
		}
	}

	void DeleteNode(TTypedTreeNode<T>* node)
	{
		if (node != nullptr)
		{
			for (int i = 0; i < node->children.size(); i++)
			{
				DeleteNode(node->children[i]);
			}
			delete node;
		}
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

	int GetDepth() const { return this->currentDepth; }

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

template<typename A>
TTypedTreeNode<A>* SearchSubTree(TTypedTreeNode<A>* subtree, std::function<bool(A)> searchFunc)
{
	if (searchFunc(subtree->object))
	{
		return subtree;
	}
	if (subtree->children.size() == 0)
	{
		return nullptr;
	}

	for (int i = 0; i < subtree->children.size(); i++)
	{
		TTypedTreeNode<A>* temp = SearchSubTree(subtree->children[i], searchFunc);
		if (temp != nullptr)
		{
			return temp;
		}
	}
	return nullptr;
}

template<typename A>
TTypedTreeNode<A>* SearchTree(TTypedTree<A>* tree, std::function<bool(A)> searchFunc)
{
	if (searchFunc(tree->GetRoot()->object))
	{
		return tree->GetRoot();
	}
	
	for (int i = 0; i < tree->GetRoot()->children.size(); i++)
	{
		TTypedTreeNode<A>* temp = SearchSubTree(tree->GetRoot()->children[i], searchFunc);
		if (temp != nullptr)
		{
			return temp;
		}
	}
	return nullptr;
}

template<typename A, typename B>
void MakeSubtreeFromBase(TTypedTreeNode<A>* from, TTypedTreeNode<B>* to, std::function<B(A)> convertFunc)
{
	for (int i = 0; i < from->children.size(); i++)
	{
		to->AddChild(convertFunc(from->object));
		MakeSubtreeFromBase(from->children[i], to->children[i], convertFunc);
	}
}

template<typename A, typename B>
void MakeTreeFromBase(TTypedTree<A>* from, TTypedTree<B>* to, std::function<B(A)> convertFunc)
{
	if (to == nullptr)
	{
		Debug::LogError("To is Null");
		return;
	}

	to->Empty();
	to->CreateRoot(convertFunc(from->GetRootObject()));
	std::vector<TTypedTreeNode<A>*> fromChildren = from->GetRoot()->children;

	for (int i = 0; i < fromChildren.size(); i++)
	{
		to->GetRoot()->AddChild(convertFunc(fromChildren[i]->object));
		MakeSubtreeFromBase(fromChildren[i], to->GetRoot()->children[i], convertFunc);
	}
}

template<typename A, typename B>
TTypedTreeNode<B>* SearchCorrespondingSubtrees(TTypedTreeNode<A>* subtreeOne, TTypedTreeNode<B>* subtreeTwo, std::function<bool(A)> searchFunc)
{
	if (searchFunc(subtreeOne->object))
	{
		return subtreeTwo;
	}
	if (subtreeOne->children.size() == 0)
	{
		return nullptr;
	}

	for (int i = 0; i < subtreeOne->children.size(); i++)
	{
		TTypedTreeNode<B>* temp = SearchCorrespondingSubtrees(subtreeOne->children[i], subtreeTwo->children[i], searchFunc);
		if (temp != nullptr)
		{
			return temp;
		}
	}
	return nullptr;
}

template<typename A, typename B>
TTypedTreeNode<B>* SearchCorrespondingTrees(TTypedTree<A>* treeOne, TTypedTree<B>* treeTwo, std::function<bool(A)> searchFunc)
{
	if (searchFunc(treeOne->GetRootObject()))
	{
		return treeTwo->GetRoot();
	}

	for (int i = 0; i < treeOne->GetRoot()->children.size(); i++)
	{
		TTypedTreeNode<B>* temp = SearchCorrespondingSubtrees(treeOne->GetRoot()->children[i], treeTwo->GetRoot()->children[i], searchFunc);
		if (temp != nullptr)
		{
			return temp;
		}
	}
}
