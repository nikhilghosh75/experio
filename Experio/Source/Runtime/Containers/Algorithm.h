#pragma once
#include <vector> // Will be deleted once TArray and TList become integrated
#include "TArray.h"
#include "THashtable.h"
#include "TQueue.h"
#include "TTypedTree.h"
#include "TUnrolledList.h"

namespace Experio::Algorithm
{
	template<typename T>
	std::vector<T> GetUnique(const std::vector<T>& v);

	template<typename T>
	TArray<T> GetUnique(const TArray<T>& array);

	template<typename T>
	TArray<T> GetUnique(const TQueue<T>& queue);

	template<typename T>
	TArray<T> GetUnique(const TTypedTree<T>& tree);

	template<typename T>
	TArray<T> GetUnique(const TUnrolledList<T>& list);

	template<typename T>
	std::vector<std::pair<T, uint32_t>> UniqueCount(const std::vector<T>& v);

	template<typename T>
	TArray<std::pair<T, uint32_t>> UniqueCount(const TArray<T>& array);

	template<typename T>
	TArray<std::pair<T, uint32_t>> UniqueCount(const TQueue<T>& queue);

	template<typename T>
	TArray<std::pair<T, uint32_t>> UniqueCount(const TTypedTree<T>& tree);

	template<typename T>
	TArray<std::pair<T, uint32_t>> UniqueCount(const TUnrolledList<T>& list);

	template<typename T>
	bool ExistsIn(const std::vector<T>& vector, const T& element);

	template<typename T>
	bool ExistsIn(const TArray<T>& array, const T& element);

	template<typename K, typename V, typename F>
	bool ExistsIn(const THashtable<K, V, F> hashtable, const K& key);

	template<typename K, typename V, typename F>
	bool ExistsIn(const THashtable<K, V, F> hashtable, const V& value);

	template<typename T>
	bool ExistsIn(const TQueue<T>& queue, const T& element);

	template<typename T>
	bool ExistsIn(const TTypedTree<T>& tree, const T& element);

	template<typename T>
	bool ExistsIn(const TUnrolledList<T>& list, const T& element);

	template<typename T>
	void RemoveElement(std::vector<T>& v, const T& element);

	template<typename T>
	void RemoveElement(TArray<T>& array, const T& element);

	template<typename T>
	void RemoveElement(TQueue<T>& queue, const T& element);

	template<typename T>
	void RemoveElement(TUnrolledList<T>& list, const T& element);

	template<typename T>
	void RemoveAt(std::vector<T>& v, uint32_t index);

	template<typename T>
	void RemoveAt(TArray<T>& array, uint32_t index);

	template<typename T>
	void RemoveAt(TQueue<T>& queue, uint32_t index);

	template<typename T>
	void RemoveAt(TUnrolledList<T>& list, uint32_t index);

	template<typename T>
	bool AllOf(const std::vector<T>& vector, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool AllOf(const TArray<T>& array, std::function<bool(const T&)> compFunc);

	template<typename K, typename V, typename F>
	bool AllOf(const THashtable<K, V, F>& hashtable, std::function<bool(const K&)> compFunc);

	template<typename K, typename V, typename F>
	bool AllOf(const THashtable<K, V, F>& hashtable, std::function<bool(const K&)> compFunc);

	template<typename T>
	bool AllOf(const TQueue<T>& queue, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool AllOf(const TTypedTree<T>& tree, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool AllOf(const TUnrolledList<T>& list, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool AnyOf(const std::vector<T>& vector, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool AnyOf(const TArray<T>& array, std::function<bool(const T&)> compFunc);

	template<typename K, typename V, typename F>
	bool AnyOf(const THashtable<K, V, F>& hashtable, std::function<bool(const K&)> compFunc);

	template<typename K, typename V, typename F>
	bool AnyOf(const THashtable<K, V, F>& hashtable, std::function<bool(const K&)> compFunc);

	template<typename T>
	bool AnyOf(const TQueue<T>& queue, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool AnyOf(const TTypedTree<T>& tree, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool AnyOf(const TUnrolledList<T>& list, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool NoneOf(const std::vector<T>& vector, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool NoneOf(const TArray<T>& array, std::function<bool(const T&)> compFunc);

	template<typename K, typename V, typename F>
	bool NoneOf(const THashtable<K, V, F>& hashtable, std::function<bool(const K&)> compFunc);

	template<typename K, typename V, typename F>
	bool NoneOf(const THashtable<K, V, F>& hashtable, std::function<bool(const K&)> compFunc);

	template<typename T>
	bool NoneOf(const TQueue<T>& queue, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool NoneOf(const TTypedTree<T>& tree, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool NoneOf(const TUnrolledList<T>& list, std::function<bool(const T&)> compFunc);

	template<typename T>
	void ForEach(std::vector<T>& vector, std::function<void(T&)> func);

	template<typename T>
	void ForEach(TArray<T>& array, std::function<void(T&)> func);

	template<typename K, typename V, typename F>
	void ForEach(THashtable<K, V, F> hashtable, std::function<void(K&)> func);

	template<typename K, typename V, typename F>
	void ForEach(THashtable<K, V, F> hashtable, std::function<void(V&)> func);

	template<typename T>
	void ForEach(TQueue<T>& queue, std::function<void(T&)> func);

	template<typename T>
	void ForEach(TTypedTree<T>& tree, std::function<void(T&)> func);

	template<typename T>
	void ForEach(TUnrolledList<T>& list, std::function<void(T&)> func);

	template<typename T>
	T* Find(std::vector<T>& vector, const T& elem);

	template<typename T>
	T* Find(TArray<T>& array, const T& elem);

	template<typename K, typename V, typename F>
	K* Find(THashtable<K, V, F>& hashtable, const K& elem);

	template<typename T>
	T* Find(TQueue<T> queue, const T& elem);

	template<typename T>
	T* Find(TTypedTree<T>& tree, const T& elem);

	template<typename T>
	T* Find(TUnrolledList<T>& list, const T& elem);

	template<typename T>
	T* Find(std::vector<T>& vector, std::function<bool(T&)> func);

	template<typename T>
	T* Find(TArray<T>& array, std::function<bool(T&)> func);

	template<typename K, typename V, typename F>
	K* Find(THashtable<K, V, F>& hashtable, std::function<bool(K&)> func);

	template<typename T>
	T* Find(TQueue<T> queue, std::function<bool(T&)> func);

	template<typename T>
	T* Find(TTypedTree<T>& tree, std::function<bool(T&)> func);

	template<typename T>
	T* Find(TUnrolledList<T>& list, std::function<bool(T&)> func);

	template<typename T>
	const T* Find(const std::vector<T>& vector, const T& elem);

	template<typename T>
	const T* Find(const TArray<T>& array, const T& elem);

	template<typename K, typename V, typename F>
	const K* Find(const THashtable<K, V, F>& hashtable, const K& elem);

	template<typename T>
	const T* Find(const TQueue<T> queue, const T& elem);

	template<typename T>
	const T* Find(const TTypedTree<T>& tree, const T& elem);

	template<typename T>
	const T* Find(const TUnrolledList<T>& list, const T& elem);

	template<typename T>
	const T* Find(const std::vector<T>& vector, std::function<bool(const T&)> func);

	template<typename T>
	const T* Find(const TArray<T>& array, std::function<bool(const T&)> func);

	template<typename K, typename V, typename F>
	const K* Find(const THashtable<K, V, F>& hashtable, std::function<bool(const K&)> func);

	template<typename T>
	const T* Find(const TQueue<T> queue, std::function<bool(const T&)> func);

	template<typename T>
	const T* Find(const TTypedTree<T>& tree, std::function<bool(const T&)> func);

	template<typename T>
	const T* Find(const TUnrolledList<T>& list, std::function<bool(const T&)> func);

	// ---------------------------------------------------------------------------------

	template<typename T>
	bool ExistsIn(const std::vector<T>& vector, const T & element)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] == element)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	bool ExistsIn(const TTypedTree<T>& tree, const T & element)
	{
		TTypedTreeNode<T>* foundElem = SearchTree(&tree, [element](T elem) {
			return element == elem;
		});
		return foundElem != nullptr;
	}

	template<typename T>
	void RemoveElement(std::vector<T>& vector, const T & element)
	{
		bool found = false;
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] == element)
			{
				found = true;
			}
			else if (found)
			{
				vector[i - 1] = vector[i];
			}
		}
		if(found) vector.pop_back();
	}

	template<typename T>
	void RemoveAt(std::vector<T>& v, uint32_t index)
	{
		for (int i = index; i < v.size() - 1; i++)
		{
			v[i] = v[i + 1];
		}
		v.pop_back();
	}

	template<typename T>
	T * Find(std::vector<T>& vector, std::function<bool(T&)> func)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			if (func(vector[i])) return &vector[i];
		}
		return nullptr;
	}

	template<typename T>
	const T* Find(const std::vector<T>& vector, std::function<bool(const T&)> func)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			if (func(vector[i])) return &vector[i];
		}
		return nullptr;
	}
}
