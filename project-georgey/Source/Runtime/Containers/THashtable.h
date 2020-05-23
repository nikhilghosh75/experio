#pragma once

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

	K GetKey() const { return key; }
	V GetValue() const { return value; }
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
	THashtable();
	~THashtable();

	V& Get(const K& key);
	bool SafeGet(const K& key, V& value);

	unsigned long GetHashCode(K key);

	void Insert(const K& key, const V& value);

	void Remove(const K& key);

	void Empty();

	void Resize(unsigned int newCapacity);

	unsigned int GetSize() const { return size; }
	unsigned int GetCapacity() const { return capacity; }
};