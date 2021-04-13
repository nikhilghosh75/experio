#pragma once

#include <functional>
#include "TBinarySearchTree.h"

template<typename K, typename V>
struct TMapNode
{
	K key;
	V value;

	bool operator==(const TMapNode<K, V>& other) const
	{
		return this->key == other.key;
	}
};

template<typename K, typename V, class Compare = std::less<K>>
class TMap
{
	struct MapCompare
	{
		Compare cmp;

		bool operator()(const TMapNode<K, V>& node1, const TMapNode<K, V>& node2) const
		{
			return cmp(node1.key, node2.key);
		}
	};

	TBinarySearchTree<TMapNode<K, V>, MapCompare> tree;
public:
	TMap()
	{

	}

	TMap(const K* keys, const V* values, int num)
	{
		for (int i = 0; i < num; i++)
		{
			tree.Insert(TMapNode(keys[i], values[i]));
		}
	}

	bool ExistsIn(const K& key) const
	{
		return tree.Find({ key, V() });
	}

	bool ExistsIn(const V& value) const
	{
		bool existsIn = false;

		tree.ForEachInOrder([value, &existsIn](const TMapNode<K, V>& node) { if (value == node.value) existsIn = true; });

		return existsIn;
	}

	V& Get(const K& key)
	{
		auto* foundNode = tree.Find({ key, V() });

		if (foundNode != nullptr)
		{
			return foundNode->value;
		}

		return tree.root.object.value;
	}

	const V& Get(const K& key) const
	{
		const auto* foundNode = tree.Find({ key, V() });

		if (foundNode != nullptr)
		{
			return foundNode->value;
		}

		return tree.root.object.value;
	}

	bool SafeGet(const K& key, V& value)
	{
		const auto* foundNode = tree.Find({ key, V() });

		if (foundNode != nullptr)
		{
			value = foundNode->value;
			return true;
		}
		return false;
	}

	bool SafeGet(const K& key, const V& value) const
	{
		const auto* foundNode = tree.Find({ key, V() });

		if (foundNode != nullptr)
		{
			value = foundNode->value;
			return true;
		}
		return false;
	}

	void Insert(const K& key, const V& value)
	{
		tree.Insert({ key, value });
	}

	void Insert(const TPair<K, V>& pair)
	{
		tree.Insert({ pair.first, pair.second });
	}

	void Remove(const K& key)
	{
		tree.Remove({ key, V() });
	}

	void Empty()
	{
		tree.Clear();
	}

	bool Find(const V& value, K& foundKey)
	{
		bool found = false;
		tree.ForEachInOrder([&found, &foundKey](TMapNode<K, V>& node) {
			if (node.value == value)
			{
				found = true;
				foundKey = node.key;
			}
		});

		return found;
	}

	bool SearchKeys(K& foundKey, V& foundValue, std::function<bool(K&)> searchFunc)
	{
		bool found = false;
		tree.ForEachInOrder([&found, &foundKey, &foundValue, searchFunc](TMapNode<K, V>& node) 
		{
			if (searchFunc(node.key))
			{
				found = true;
				foundKey = node.key;
				foundValue = node.value;
			}
		});

		return found;
	}

	bool SearchValues(K& foundKey, V& foundValue, std::function<bool(V&)> searchFunc)
	{
		bool found = false;
		tree.ForEachInOrder([&found, &foundKey, &foundValue, searchFunc](TMapNode<K, V>& node)
			{
				if (searchFunc(node.value))
				{
					found = true;
					foundKey = node.key;
					foundValue = node.value;
				}
			});

		return found;
	}

	void ForEach(std::function<void(K&, V&)> func)
	{
		tree.ForEachInOrder([func](TMapNode<K, V>& node) {
			func(node.key, node.value);
		});
	}

	unsigned int GetSize() const { return tree.Count(); }
};