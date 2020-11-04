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
	void RemoveElement(const std::vector<T>& v, const T& element);

	template<typename T>
	void RemoveElement(const TArray<T>& array, const T& element);

	template<typename T>
	void RemoveElement(const TQueue<T>& queue, const T& element);

	template<typename T>
	void RemoveElement(const TUnrolledList<T>& list, const T& element);

	template<typename T>
	bool ExistsIn(const std::vector<T>& vector, const T & element)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] == object)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	void RemoveElement(const std::vector<T>& v, const T & element)
	{
		bool found = false;
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] == object)
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
}

