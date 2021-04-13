#pragma once
#include <functional>
#include "TBinarySearchTree.h"

template<class T, class Compare = std::less<T>>
class TSet
{
	TBinarySearchTree<T, Compare> tree;

public:
	TSet()
	{

	}

	TSet(std::initializer_list<T> list)
	{
		tree = TBinarySearchTree<T>(list);
	}

	size_t Count() const
	{
		return tree.Count();
	}

	void Insert(const T& item)
	{
		tree.Insert(item);
	}

	bool Exists(const T& item) const
	{
		return tree.Find() != nullptr;
	}

	const T* Find(const T& item) const
	{
		return tree.Find();
	}

	static TSet<T> Merge(TSet<T>& setOne, TSet<T>& setTwo)
	{
		TSet<T> set;
		setOne.tree.ForEachPreOrder([&set](T& item) {set.Insert(set)});
		setTwo.tree.ForEachPreOrder([&set](T& item) {set.Insert(set)});
		return set;
	}

	void Remove(const T& item)
	{
		tree.Remove(item);
	}
};