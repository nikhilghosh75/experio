#pragma once

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

	bool IsRoot() const;
	bool IsParent() const;
	bool IsChild() const;

	void AddChild(T newObject);
	void DeleteChild(int index);
};

template <class T>
class TTypedTree
{
	unsigned int count;
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

void TTypedTreeTest();