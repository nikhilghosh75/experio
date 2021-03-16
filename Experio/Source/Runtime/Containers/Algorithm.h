#pragma once
#include <vector>
#include "TArray.h"
#include "THashtable.h"
#include "TQueue.h"
#include "TTypedTree.h"
#include "TUnrolledList.h"

/// <summary>
/// A list of algorithms meant for templated classes
/// </summary>

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
	bool NotAllOf(const std::vector<T>& vector, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool NotAllOf(const TArray<T>& array, std::function<bool(const T&)> compFunc);

	template<typename K, typename V, typename F>
	bool NotAllOf(const THashtable<K, V, F>& hashtable, std::function<bool(const K&)> compFunc);

	template<typename K, typename V, typename F>
	bool NotAllOf(const THashtable<K, V, F>& hashtable, std::function<bool(const K&)> compFunc);

	template<typename T>
	bool NotAllOf(const TQueue<T>& queue, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool NotAllOf(const TTypedTree<T>& tree, std::function<bool(const T&)> compFunc);

	template<typename T>
	bool NotAllOf(const TUnrolledList<T>& list, std::function<bool(const T&)> compFunc);

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
	const uint32_t Mismatch(std::vector<T>& vector1, std::vector<T>& vector2);

	template<typename T>
	const uint32_t Mismatch(TArray<T>& array1, std::vector<T>& array2);

	template<typename T>
	const uint32_t Mismatch(TUnrolledList<T>& array1, TUnrolledList<T>& array2);

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

	template<typename T>
	void AddNumOf(std::vector<T>& vector, T elem, size_t num);

	template<typename T>
	void AddNumOf(TArray<T>& array, T elem, size_t num);

	template<typename T>
	void AddNumOf(TQueue<T>& queue, T elem, size_t num);

	template<typename T>
	void AddNumOf(TUnrolledList<T>& list, T elem, size_t num);

	template<typename T>
	void InsertAt(std::vector<T>& vector, T elem, size_t position);

	// ---------------------------------------------------------------------------------

	template<typename T>
	std::vector<T> GetUnique(const std::vector<T>& v)
	{
		std::vector<T> unique;
		unique.reserve(v.size());
		unique.push_back(v[0]);

		for (uint32_t i = 1; i < v.size(); i++)
		{
			bool found = false;
			for (uint32_t j = 0; j < unique.size(); j++)
			{
				if (unique[j] == v[i])
				{
					found = true; break;
				}
			}
			if (!found)
			{
				unique.push_back(v[i]);
			}
		}
		return unique;
	}

	template<typename T>
	TArray<T> GetUnique(const TArray<T>& array)
	{
		TArray<T> unique;
		unique.Resize(array.Count());
		unique.Append(array[0]);

		for (uint32_t i = 1; i < array.Count(); i++)
		{
			bool found = false;
			for (uint32_t j = 0; j < unique.Count(); j++)
			{
				if (unique[j] == array[i])
				{
					found = true; break;
				}
			}
			if (!found)
			{
				unique.Append(array[i]);
			}
		}

		return unique;
	}

	template<typename T>
	TArray<T> GetUnique(const TQueue<T>& queue)
	{
		TArray<T> unique;
		unique.Resize(queue.Count());
		unique.Append(queue.Peek());

		for (uint32_t i = 1; i < queue.Count(); i++)
		{
			T elem = queue.PeekAt(i);
			bool found = false;
			for (uint32_t j = 0; j < unique.Count(); j++)
			{
				if (unique[j] == elem)
				{
					found = true; break;
				}
			}
			if (!found)
			{
				unique.Append(elem);
			}
		}

		return unique;
	}

	template<typename T>
	std::vector<std::pair<T, uint32_t>> UniqueCount(const std::vector<T>& v)
	{
		std::vector<std::pair<T, uint32_t>> unique;
		unique.reserve(v.size());
		unique.emplace_back(v[0], 1);

		for (uint32_t i = 1; i < v.size(); i++)
		{
			bool found = false;
			size_t foundIndex = 0;
			for (uint32_t j = 0; j < unique.size(); j++)
			{
				if (unique[j].first == v[i])
				{
					found = true; foundIndex = i; break;
				}
			}
			if (found)
				unique[foundIndex].second++;
			else
				unique.emplace_back(v[i], 1);
		}

		return unique;
	}

	template<typename T>
	TArray<std::pair<T, uint32_t>> UniqueCount(const TArray<T>& array)
	{
		std::vector<std::pair<T, uint32_t>> unique;
		unique.reserve(array.Count());
		unique.emplace_back(array[0], 1);

		for (uint32_t i = 1; i < array.Count(); i++)
		{
			bool found = false;
			size_t foundIndex = 0;
			for (uint32_t j = 0; j < unique.Count(); j++)
			{
				if (unique[j] == array[i])
				{
					found = true; foundIndex = i; break;
				}
			}
			if (found)
				unique[foundIndex].second++;
			else
				unique.emplace_back(array[i], 1);
		}

		return unique;
	}

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
	bool AllOf(const std::vector<T>& vector, std::function<bool(const T&)> compFunc)
	{
		for (size_t i = 0; i < vector.size(); i++)
		{
			if (!compFunc(vector[i]))
				return false;
		}
		return true;
	}

	template<typename T>
	bool AllOf(const TArray<T>& array, std::function<bool(const T&)> compFunc)
	{
		for (size_t i = 0; i < array.Count(); i++)
		{
			if (!compFunc(array[i]))
				return false;
		}
		return true;
	}

	template<typename T>
	bool NotAllOf(const std::vector<T>& vector, std::function<bool(const T&)> compFunc)
	{
		for (size_t i = 0; i < array.Count(); i++)
		{
			if (!compFunc(array[i]))
				return true;
		}
		return false;
	}

	template<typename T>
	bool AnyOf(const std::vector<T>& vector, std::function<bool(const T&)> compFunc)
	{
		for (size_t i = 0; i < array.Count(); i++)
		{
			if (compFunc(array[i]))
				return true;
		}
		return false;
	}

	template<typename T>
	bool NoneOf(const std::vector<T>& vector, std::function<bool(const T&)> compFunc)
	{
		for (size_t i = 0; i < array.Count(); i++)
		{
			if (compFunc(array[i]))
				return false;
		}
		return true;
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

	template<typename T>
	void AddNumOf(std::vector<T>& vector, T elem, size_t num)
	{
		for (size_t i = 0; i < num; i++)
		{
			vector.push_back(elem);
		}
	}

	template<typename T>
	void InsertAt(std::vector<T>& vector, T elem, size_t position)
	{
		if (vector.size() == 0)
		{
			vector.push_back(elem);
			return;
		}

		vector.push_back(vector[vector.size() - 1]);

		for (size_t i = vector.size() - 1; i > position ; i--)
		{
			vector[i] = vector[i - 1];
		}

		vector[position] = elem;
	}
}

