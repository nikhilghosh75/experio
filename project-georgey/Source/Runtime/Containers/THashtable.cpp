#include "THashtable.h"

#define HASHTABLE_START_CAPACITY 8

THashtable<int, int> doubleInts;

template<typename K, typename V, typename F>
THashtable<K, V, F>::THashtable()
{
	this->capacity = HASHTABLE_START_CAPACITY;
	this->arr = new THashNode<K, V>*[HASHTABLE_START_CAPACITY]();
	this->size = 0;
	this->hashFunction.tableCapacity = HASHTABLE_START_CAPACITY;
}

template<typename K, typename V, typename F>
THashtable<K, V, F>::~THashtable()
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

template<typename K, typename V, typename F>
V& THashtable<K, V, F>::Get(const K & key)
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

	return nullptr;
}

template<typename K, typename V, typename F>
bool THashtable<K, V, F>::SafeGet(const K & key, V & value)
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

template<typename K, typename V, typename F>
unsigned long THashtable<K, V, F>::GetHashCode(K key)
{
	return hashFunction(key);
}

template<typename K, typename V, typename F>
void THashtable<K, V, F>::Insert(const K & key, const V & value)
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

template<typename K, typename V, typename F>
void THashtable<K, V, F>::Remove(const K & key)
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

template<typename K, typename V, typename F>
void THashtable<K, V, F>::Empty()
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

template<typename K, typename V, typename F>
void THashtable<K, V, F>::Resize(unsigned int newCapacity)
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
