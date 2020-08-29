#pragma once
#include <string>

#define HASHTABLE_START_CAPACITY 8

template<typename K, typename V>
class THashNode
{
	V value;
	K key;

	THashNode* nextNode;
public:
	THashNode(K key, V value)
	{
		this->value = value;
		this->key = key;
		nextNode = nullptr;
	}

	K& GetKey() { return key; }
	V& GetValue() { return value; }
	THashNode* GetNext() const { return nextNode; }

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
		return reinterpret_cast<unsigned long>(key) % tableCapacity;
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

	~THashtable()
	{
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
		delete[] arr;
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

	void Empty()
	{
		this->size = 0;
		for (int i = 0; i < this->capacity; i++)
		{
			THashNode<K, V>* entry = arr[i];
			while (entry != nullptr)
			{
				THashNode<K, V>* prev = entry;
				entry = prev->nextNode;
				delete prev;
			}
			arr[i] = nullptr;
		}
	}

	void Resize(unsigned int newCapacity)
	{
		// Get all keys
		K keys[this->size];
		V values[this->size];

		if (this->size != 0)
		{
			int i = 0;
			for (int j = 0; j < this->capacity; j++)
			{
				THashNode<K, V>* entry = arr[j];
				while (entry != nullptr)
				{
					THashNode<K, V>* prev = entry;
					entry = prev->nextNode;
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
	}

	unsigned int GetSize() const { return size; }
	unsigned int GetCapacity() const { return capacity; }
};

void THashtableTest();

struct StringHashFunction
{
public:
	unsigned int tableCapacity;

	unsigned long operator()(const std::string& key) const
	{
		return (key[0] + key.size()) % tableCapacity;
	}
};