#pragma once
#include <string>
#include <functional>
#include <vector>
#include "TPair.h"

#define HASHTABLE_START_CAPACITY 8

template<typename K, typename V>
class THashNode
{
	K key;
	V value;

	THashNode* nextNode;
public:
	THashNode()
	{
		this->nextNode = nullptr;
	}

	THashNode(K key, V value)
	{
		this->value = value;
		this->key = key;
		nextNode = nullptr;
	}

	K& GetKey() { return key; }
	V& GetValue() { return value; }
	THashNode* GetNext() const { return nextNode; }

	void SetKey(K key)
	{
		this->key = key;
	}

	void SetValue(V value)
	{
		this->value = value;
	}

	void SetNext(THashNode* next)
	{
		this->nextNode = next;
	}
};

template<typename K>
struct HashFunction 
{
public:
	unsigned int tableCapacity;

	unsigned long operator()(const K& key) const
	{
		return static_cast<unsigned long>(key) % tableCapacity;
	}
};

template<typename K, typename V, typename F = HashFunction<K>>
class THashtable
{
	THashNode<K, V>** arr;

	unsigned int capacity;
	unsigned int size;

	F hashFunction;

public:
	THashtable()
	{
		this->capacity = HASHTABLE_START_CAPACITY;
		this->arr = new THashNode<K, V>*[HASHTABLE_START_CAPACITY]();
		this->size = 0;
		this->hashFunction.tableCapacity = HASHTABLE_START_CAPACITY;
	}

	THashtable(const K* keys, const V* values, int num)
	{
		this->capacity = HASHTABLE_START_CAPACITY;
		this->arr = new THashNode<K, V>*[HASHTABLE_START_CAPACITY]();
		this->size = 0;
		this->hashFunction.tableCapacity = HASHTABLE_START_CAPACITY;

		for (int i = 0; i < num; i++)
		{
			Insert(K[i], V[i]);
		}
	}

	THashtable(const THashtable<K, V, F>& hashtable)
	{
		this->capacity = hashtable.capacity;
		this->arr = new THashNode<K, V>*[this->capacity]();
		
		for (int i = 0; i < this->capacity; i++)
		{
			this->arr[i] = new THashNode<K, V>();
			THashNode<K, V>* thisEntry = this->arr[i];
			THashNode<K, V>* otherEntry = hashtable.arr[i];
			while (otherEntry != nullptr)
			{
				thisEntry->SetKey(otherEntry->GetKey());
				thisEntry->SetValue(otherEntry->GetValue());
				if (otherEntry->GetNext() != nullptr)
				{
					thisEntry->SetNext(new THashNode<K, V>());
					otherEntry = otherEntry->GetNext();
					thisEntry = thisEntry->GetNext();
				}
				else
				{
					break;
				}
			}
		}

		this->size = hashtable.size;
	}

	~THashtable()
	{
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				THashNode<K, V>* prev = entry;
				if (prev == nullptr) break;
				entry = prev->GetNext();
				delete prev;
			}
			arr[i] = nullptr;
		}
		delete[] arr;
	}

	bool ExistsIn(const K& key) const
	{
		unsigned long hashValue = hashFunction(key);
		THashNode<K, V>* entry = arr[hashValue];

		while (entry != nullptr)
		{
			if (entry->GetKey() == key)
			{
				return true;
			}
			entry = entry->GetNext();
		}
		return false;
	}

	bool ExistsIn(const V& value) const
	{
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				if (entry->GetValue() == value)
				{
					return true;
				}
				entry = entry->GetNext();
			}
		}
		return false;
	}

	V& Get(const K& key)
	{
		unsigned long hashValue = hashFunction(key);
		THashNode<K, V>* entry = arr[hashValue];

		while (entry != nullptr)
		{
			if (entry->GetKey() == key)
			{
				return entry->GetValue();
			}
			entry = entry->GetNext();
		}
	}

	const V& Get(const K& key) const
	{
		unsigned long hashValue = hashFunction(key);
		THashNode<K, V>* entry = arr[hashValue];

		while (entry != nullptr)
		{
			if (entry->GetKey() == key)
			{
				return entry->GetValue();
			}
			entry = entry->GetNext();
		}
	}

	bool SafeGet(const K& key, V& value)
	{
		unsigned long hashValue = hashFunction(key);
		THashNode<K, V>* entry = arr[hashValue];

		while (entry != nullptr)
		{
			if (entry->GetKey() == key)
			{
				value = entry->GetValue();
				return true;
			}
			entry = entry->GetNext();
		}

		return false;
	}

	bool Set(const K& key, const V& newValue)
	{
		unsigned long hashValue = hashFunction(key);
		THashNode<K, V>* entry = arr[hashValue];

		while (entry != nullptr)
		{
			if (entry->GetKey() == key)
			{
				entry->SetValue(newValue);
				return true;
			}
			entry = entry->GetNext();
		}

		return false;
	}

	unsigned long GetHashCode(K key)
	{
		return hashFunction(key);
	}

	void Insert(const K& key, const V& value)
	{
		unsigned long hashValue = hashFunction(key);
		THashNode<K, V>* prev = nullptr;
		THashNode<K, V>* entry = arr[hashValue];

		while (entry != nullptr && entry->GetKey() != key)
		{
			prev = entry;
			entry = entry->GetNext();
		}

		if (entry == nullptr)
		{
			entry = new THashNode<K, V>(key, value);
			if (prev == nullptr)
			{
				arr[hashValue] = entry;
			}
			else
			{
				prev->SetNext(entry);
			}
			this->size++;
		}
		else
		{
			entry->SetValue(value);
		}
	}

	void Insert(const TPair<K, V>& pair)
	{
		Insert(pair.first, pair.second);
	}

	void Remove(const K& key)
	{
		unsigned long hashValue = hashFunction(key);
		THashNode<K, V>* prev = nullptr;
		THashNode<K, V>* entry = arr[hashValue];

		while (entry != nullptr && entry->GetKey() != key)
		{
			prev = entry;
			entry = entry->GetNext();
		}

		if (entry == nullptr)
		{
			return;
		}
		else
		{
			if (prev == nullptr)
			{
				arr[hashValue] = entry->GetNext();
			}
			else
			{
				prev->SetNext(entry->GetNext());
			}
			delete entry;
			this->size--;
		}
	}

	void RemoveValue(const V& value)
	{
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				THashNode<K, V>* prev = entry;
				if (entry->GetValue() == value)
				{
					prev->SetNext(entry->GetNext());
					entry = entry->GetNext();
					delete prev->GetNext();
					this->size--;
				}
				if (entry != nullptr)
				{
					entry = entry->GetNext();
				}
			}
		}
	}

	void Empty()
	{
		this->size = 0;
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				THashNode<K, V>* prev = entry;
				entry = prev->GetNext();
				delete prev;
			}
			arr[i] = nullptr;
		}
	}

	void Resize(unsigned int newCapacity)
	{
		// Get all keys
		K* keys = new K[this->size];
		V* values = new V[this->size];

		if (this->size != 0)
		{
			int i = 0;
			for (int j = 0; j < this->capacity; j++)
			{
				THashNode<K, V>* entry = arr[j];
				while (entry != nullptr)
				{
					THashNode<K, V>* prev = entry;
					entry = prev->GetNext();
					keys[i] = prev->GetKey();
					values[i] = prev->GetValue();
					i++;
					delete prev;
				}
			}
		}

		delete this->arr;
		this->arr = new THashNode<K, V>*[newCapacity]();
		this->capacity = newCapacity;
		hashFunction.tableCapacity = newCapacity;

		if (this->size == 0)
		{
			return;
		}

		for (int i = 0; i < this->size; i++)
		{
			this->Insert(keys[i], values[i]);
		}

		delete keys;
		delete values;
	}

	bool Find(const V& value, K& foundKey)
	{
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				if (entry->GetValue() == value)
				{
					foundKey = entry->GetKey();
					return true;
				}
				entry = entry->GetNext();
			}
		}
		return false;
	}

	bool SearchKeys(K& foundKey, V& foundValue, std::function<bool(K&)> searchFunc)
	{
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				if (searchFunc(entry->GetKey()))
				{
					foundKey = entry->GetKey();
					foundValue = entry->GetValue();
					return true;
				}
				entry = entry->GetNext();
			}
		}
		return false;
	}

	bool SearchValues(K& foundKey, V& foundValue, std::function<bool(V&)> searchFunc)
	{
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				if (searchFunc(entry->GetValue()))
				{
					foundKey = entry->GetKey();
					foundValue = entry->GetValue();
					return true;
				}
				entry = entry->GetNext();
			}
		}
		return false;
	}

	void ForEach(std::function<void(K&, V&)> func)
	{
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				func(entry->GetKey(), entry->GetValue());
				entry = entry->GetNext();
			}
		}
	}

	void ForEach(std::function<void(const K&, const V&)> func) const
	{
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				func(entry->GetKey(), entry->GetValue());
				entry = entry->GetNext();
			}
		}
	}

	std::vector<TPair<K, V>> GetPairs() const
	{
		std::vector<TPair<K, V>> pairs;
		pairs.reserve(this->size);
		
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				pairs.emplace_back(entry->GetKey(), entry->GetValue());
				entry = entry->GetNext();
			}
		}
		return pairs;
	}

	unsigned int GetSize() const { return size; }
	unsigned int GetCapacity() const { return capacity; }
};

struct StringHashFunction
{
	unsigned int tableCapacity;

	unsigned long operator()(const std::string& key) const
	{
		return (key[0] + key.size()) % tableCapacity;
	}
};

template<typename T>
struct PointerHashFunction
{
	unsigned int tableCapacity;

	unsigned long operator()(const T* key) const
	{
		return reinterpret_cast<unsigned long>(key) % tableCapacity;
	}
};