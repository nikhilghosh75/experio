#pragma once
#include <functional>
#include <stdint.h>
#include <initializer_list>

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
		count = 1;
	}

	uint32_t Count() const { return count; }

	uint32_t Height() const { return HeightRecursive(&this->root); }

	bool CheckInvariant() const { return CheckInvariantRecursive(&this->root;) }

	void Insert(T item)
	{
		TBinarySearchNode<T>* current = &this->root;

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

	T* Find(const T& item)
	{
		TBinarySearchNode<T>* current = &this->root;

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
				return &(current->object);
			}
		}
	}

	bool Exists(const T& item)
	{
		return Find(item) != nullptr;
	}

	void ForEachPreOrder(std::function<void(T&)> func) { ForEachPreOrderRecursive(func, &this->root); }

	void ForEachInOrder(std::function<void(T&)> func) { ForEachInOrderRecursive(func, &this->root); }

	void ForEachPostOrder(std::function<void(T&)> func) { ForEachPostOrderRecursive(func, &this->root); }

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

	bool HasChildren(const TBinarySearchNode<T>* node)
	{
		return node->left != nullptr || node->right != nullptr;
	}
};