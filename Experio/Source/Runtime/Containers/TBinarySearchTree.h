#pragma once
#include <functional>
#include <stdint.h>
#include <initializer_list>

/// <summary>
/// A binary tree that can be used for O(log n) searching/insertion/removal
/// </summary>

// Currently this is not implemented as a Red/Black Tree, but it will be in the future

template<class T>
class TBinarySearchNode
{
public:
	T object;
	TBinarySearchNode<T>* left;
	TBinarySearchNode<T>* right;

	TBinarySearchNode()
	{
		object = T();
		left = nullptr;
		right = nullptr;
	}

	TBinarySearchNode(T object)
	{
		this->object = object;
		this->left = nullptr;
		this->right = nullptr;
	}

	TBinarySearchNode(T object, TBinarySearchNode<T>* left, TBinarySearchNode<T>* right)
	{
		this->object = object;
		this->left = left;
		this->right = right;
	}
};

template<class T, class Compare = std::less<T>>
class TBinarySearchTree
{
	TBinarySearchNode<T> root;
	uint32_t count;
	Compare comp;
public:
	TBinarySearchTree()
	{
		count = 0;
		root.left = nullptr;
		root.right = nullptr;
	}

	TBinarySearchTree(T& rootObject)
	{
		root.object = rootObject;
		root.left = nullptr;
		root.right = nullptr;
		count = 1;
	}

	TBinarySearchTree(const TBinarySearchTree<T, Compare>& other)
	{
		this->count = other.count;
		CopyNodeRecursive(&other.root, &this->root);
	}

	TBinarySearchTree(std::initializer_list<T> list)
	{
		for (auto elem : list)
		{
			Insert(elem);
		}
	}

	~TBinarySearchTree()
	{
		DeleteNode(root.left);
		DeleteNode(root.right);
	}

	void Clear()
	{
		DeleteNode(root->left);
		DeleteNode(root->right);
		count = 0;
	}

	uint32_t Count() const { return count; }

	uint32_t Height() const { return HeightRecursive(&this->root); }

	bool CheckInvariant() const { return CheckInvariantRecursive(&this->root); }

	void Insert(T item)
	{
		if (count == 0)
		{
			root.object = item;
			count = 1;
			return;
		}

		TBinarySearchNode<T>* current = &this->root;
		count++;

		while (true)
		{
			if (comp(item, current->object))
			{
				if (current->left == nullptr)
				{
					current->left = new TBinarySearchNode<T>(item);
					return;
				}
				current = current->left;
			}
			else if (comp(current->object, item))
			{
				if (current->right == nullptr)
				{
					current->right = new TBinarySearchNode<T>(item);
					return;
				}
				current = current->right;
			}
			else
			{
				return;
			}
		}
	}

	const T* Find(const T& item) const
	{
		if (count == 0)
			return nullptr;

		const TBinarySearchNode<T>* foundNode = FindNode(item);
		if (foundNode == nullptr)
			return nullptr;
		return &(foundNode->object);
	}

	void Remove(const T& item)
	{
		if (count == 0)
			return;

		// Removal from root is a special procedure becuase we don't want to delete it
		if (!comp(root.object, item) && !comp(item, root.object))
		{
			if (root.left == nullptr && root.right == nullptr)
			{
				count = 0;
				return;
			}

			TBinarySearchNode<T>* minRightChild = MinChildRecursive(root.right);
			if (minRightChild != nullptr)
			{
				root.object = minRightChild->object;
				delete minRightChild;
				count--;
				return;
			}
			else
			{
				TBinarySearchNode<T>* maxLeftChild = MinChildRecursive(root.left);
				root.object = maxLeftChild->object;
				delete maxLeftChild;
				count--;
				return;
			}
		}

		TBinarySearchNode<T>* parent = nullptr;
		TBinarySearchNode<T>* current = &root;

		while (true)
		{
			if (comp(item, current->object))
			{
				if (current->left == nullptr)
				{
					return
				}
				parent = current;
				current = current->left;
			}
			else if (comp(current->object, item))
			{
				if (current->right == nullptr)
				{
					return;
				}
				parent = current;
				current = current->right;
			}
			else
			{
				RemoveNode(current, parent);
				count--;
				return;
			}
		}
	}

	const T& MinElement() const { return MinChildRecursive(&root); }

	const T& MaxElement() const { return MaxChildRecursive(&root); }

	bool Exists(const T& item)
	{
		return Find(item) != nullptr;
	}

	void ForEachPreOrder(std::function<void(T&)> func) 
	{ 
		if (count == 0)
			return;

		ForEachPreOrderRecursive(func, &this->root); 
	}

	void ForEachInOrder(std::function<void(T&)> func) 
	{
		if (count == 0)
			return;

		ForEachInOrderRecursive(func, &this->root); 
	}

	void ForEachPostOrder(std::function<void(T&)> func) 
	{
		if (count == 0)
			return;

		ForEachPostOrderRecursive(func, &this->root);
	}

private:
	void CopyNodeRecursive(TBinarySearchNode<T>* from, TBinarySearchNode<T>* to)
	{
		to->object = from->object;
		if (from->left != nullptr)
		{
			to->left = new TBinarySearchNode<T>();
			CopyNodeRecursive(from->left, to->left);
		}
		if (from->right != nullptr)
		{
			to->right = new TBinarySearchNode<T>();
			CopyNodeRecursive(from->right, to->right);
		}
	}

	void DeleteNode(TBinarySearchNode<T>* node)
	{
		if (node == nullptr) return;

		DeleteNode(node->left);
		DeleteNode(node->right);
		delete node;
	}

	const TBinarySearchNode<T>* FindNode(const T& item) const
	{
		const TBinarySearchNode<T>* current = &this->root;

		while (true)
		{
			if (comp(item, current->object))
			{
				if (current->left == nullptr)
				{
					return nullptr;
				}
				current = current->left;
			}
			else if (comp(current->object, item))
			{
				if (current->right == nullptr)
				{
					return nullptr;
				}
				current = current->right;
			}
			else
			{
				return current;
			}
		}
	}

	uint32_t HeightRecursive(const TBinarySearchNode<T>* node)
	{
		if (node == nullptr) return 0;

		uint32_t leftHeight = HeightRecursive(node->left);
		uint32_t rightHeight = HeightRecursive(node->right);

		if (leftHeight > rightHeight) return leftHeight + 1;
		return rightHeight + 1;
	}

	bool CheckInvariantRecursive(const TBinarySearchNode<T>* node) const
	{
		if (node == nullptr) return true;
		
		if (node->left != nullptr)
		{
			if (!comp(node->left->object, node->object))
				return false;
		}

		if (node->right != nullptr)
		{
			if (comp(node->right->object, node->object))
				return false;
		}

		return CheckInvariantRecursive(node->left) && CheckInvariantRecursive(node->right);
	}

	void ForEachPreOrderRecursive(std::function<void(T&)> func, TBinarySearchNode<T>* node)
	{
		if (node == nullptr) return;

		func(node->object);
		ForEachPreOrderRecursive(func, node->left);
		ForEachPreOrderRecursive(func, node->right);
	}

	void ForEachInOrderRecursive(std::function<void(T&)> func, TBinarySearchNode<T>* node)
	{
		if (node == nullptr) return;
		
		ForEachInOrderRecursive(func, node->left);
		func(node->object);
		ForEachInOrderRecursive(func, node->right);
	}

	void ForEachPostOrderRecursive(std::function<void(T&)> func, TBinarySearchNode<T>* node)
	{
		if (node == nullptr) return;

		ForEachInOrderRecursive(func, node->left);
		ForEachInOrderRecursive(func, node->right);
		func(node->object);
	}

	TBinarySearchNode<T>* MinChildRecursive(const TBinarySearchNode<T>* node) const
	{
		TBinarySearchNode<T>* current = node;
		while (current->left != nullptr)
		{
			current = current->left;
		}
		return current;
	}

	TBinarySearchNode<T>* MaxChildRecursive(const TBinarySearchNode<T>* node) const
	{
		TBinarySearchNode<T>* current = node;
		while (current->right != nullptr)
		{
			current = current->right;
		}
		return current;
	}

	bool HasChildren(const TBinarySearchNode<T>* node)
	{
		return node->left != nullptr || node->right != nullptr;
	}

	void RemoveNode(TBinarySearchNode<T>* node, TBinarySearchNode<T>* parent)
	{
		if (node == nullptr)
			return;

		if (node->left == nullptr && node->right == nullptr)
		{
			delete node;
			return;
		}
		
		if (node->left == nullptr)
		{
			ReplaceNode(parent, node, node->right);
			delete node;
			return;
		}
		if (node->right == nullptr)
		{
			ReplaceNode(parent, node, node->left);
			delete node;
			return;
		}

		// Current node has 2 children
		TBinarySearchNode<T>* minRightChild = MinChildRecursive(node->right);
		node->object = minRightChild->object;
		delete minRightChild;
	}

	void ReplaceNode(TBinarySearchNode<T>* parent, TBinarySearchNode<T>* toReplace, TBinarySearchNode<T>* replacement)
	{
		if (parent == nullptr)
			return;

		if (parent->left == toReplace)
		{
			parent->left = replacement;
		}
		else if (parent->right == toReplace)
		{
			parent->right = replacement;
		}
	}
};