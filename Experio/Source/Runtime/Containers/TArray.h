#pragma once
#include <cstdint>
#include <array>
#include <sstream>
#include <functional>
#include <initializer_list>

struct StandardGrowFunc
{
public:
	uint32_t operator()(const uint32_t currentCapacity)
	{
		return currentCapacity * 1.5f + 1;
	}
};

template <typename T, typename GrowFunc = StandardGrowFunc, int DefaultCapacity = 3>
class TArray
{
private:
	T* data;
	uint32_t count;
	uint32_t capacity;

	StandardGrowFunc growFunc;

	void Grow()
	{
		Resize(growFunc(this->capacity));
	}

	void Grow(uint32_t newSize)
	{
		Resize(newSize);
	}

public:

	static const uint32_t NotFound = 4294967292;
	
	TArray()
	{
		data = new T[DefaultCapacity]();
		count = 0;
		capacity = DefaultCapacity;
	}

	TArray(const T& object, uint32_t num)
	{
		data = new T[num]();
		for (uint32_t i = 0; i < num; i++)
		{
			data[i] = object;
		}
		count = num;
		capacity = num;
	}

	TArray(const T* objects, uint32_t count)
	{
		data = new T[count]();
		for (uint32_t i = 0; i < count; i++)
		{
			data[i] = objects[i];
		}
		this->count = count;
		this->capacity = count;
	}

	TArray(std::initializer_list<T> list)
	{
		data = new T[list.size()];
		this->count = 0;
		for (auto elem : list)
		{
			data[this->count] = *elem;
			this->count = 0;
		}
		this->capacity = list.size();
	}

	TArray(TArray<T>& objects)
	{
		data = new T[objects.count]();
		for (uint32_t i = 0; i < objects.count; i++)
		{
			data[i] = objects[i];
		}
		this->count = objects.count;
		this->capacity = objects.count;
	}

	// Add Move Constructor

	~TArray()
	{
		Empty();
		operator delete[](this->data);
	}

	void Append(const T& object)
	{
		if (this->count >= this->capacity)
		{
			Grow();
		}
		this->data[this->count] = object;
		this->count++;
	}

	void Append(const T* objects, uint32_t count)
	{
		if (this->count + count >= this->capacity)
		{
			Grow(this->count + count);
		}
		for (int i = 0; i < count; i++)
		{
			Append(objects[i]);
		}
	}

	void Append(const TArray<T> objects)
	{
		if (this->count + objects.count >= this->capacity)
		{
			Grow(this->count + count);
		}
		for (int i = 0; i < objects.count; i++)
		{
			Append(objects[i]);
		}
	}

	uint32_t Count() const { return count; }
	uint32_t Capacity() const { return capacity; }

	void Resize(uint32_t newCapacity)
	{
		T* newData = (T*) ::operator new(newCapacity * sizeof(T));

		for (int i = 0; i < count; i++)
		{
			newData[i] = std::move(data[i]);
		}

		::operator delete(this->data, this->capacity * sizeof(T));
		this->data = newData;
		this->capacity = newCapacity;
	}

	T& operator[](uint32_t i)
	{
		return this->data[i];
	}

	const T& operator[](uint32_t i) const
	{
		return this->data[i];
	}

	T& First() { return this->data[0]; }
	const T& First() const { return this->data[0]; }
	T& Last() { return this->data[this->count - 1]; }
	const T& Last() const { return this->data[this->count - 1]; }

	uint32_t FindIndex(const T& objectToFind) const
	{
		for (uint32_t i = 0; i < this->count; i++)
		{
			if (data[i] == objectToFind) return i;
		}
		return NotFound;
	}

	uint32_t FindIndex(const T& objectToFind, uint32_t startIndex) const
	{
		if (startIndex >= this->count) return NotFound;

		for (uint32_t i = startIndex; i < this->count; i++)
		{
			if (data[i] == objectToFind) return i;
		}
		return NotFound;
	}

	uint32_t FindIndex(std::function<bool(const T&)> findFunc) const
	{
		for (uint32_t i = 0; i < this->count; i++)
		{
			if (findFunc(data[i])) return i;
		}
		return NotFound;
	}

	uint32_t FindIndex(std::function<bool(const T&)> findFunc, uint32_t startIndex) const
	{
		if (startIndex >= this->count) return NotFound;

		for (uint32_t i = startIndex; i < this->count; i++)
		{
			if (findFunc(data[i])) return i;
		}
		return NotFound;
	}

	bool Find(const T& objectToFind, uint32_t& indexOfObject) const
	{
		for (uint32_t i = 0; i < this->count; i++)
		{
			if (data[i] == objectToFind)
			{
				indexOfObject = i;
				return true;
			}
		}
		return false;
	}

	bool Find(const T& objectToFind, uint32_t& indexOfObject, uint32_t startIndex) const
	{
		if (startIndex >= this->count) return false;

		for (uint32_t i = startIndex; i < this->count; i++)
		{
			if (data[i] == objectToFind)
			{
				indexOfObject = i;
				return true;
			}
		}
		return false;
	}

	bool Find(std::function<bool(const T&)> findFunc, uint32_t& indexOfObject) const
	{
		for (uint32_t i = 0; i < this->count; i++)
		{
			if (findFunc(data[i]))
			{
				indexOfObject = i;
				return true;
			}
		}
		return false;
	}

	bool Find(std::function<bool(const T&)> findFunc, uint32_t& indexOfObject, uint32_t startIndex)
	{
		if (startIndex >= this->count) return false;

		for (uint32_t i = startIndex; i < this->count; i++)
		{
			if (findFunc(data[i]))
			{
				indexOfObject = i;
				return true;
			}
		}
		return false;
	}
	
	TArray<uint32_t> FindAll(const T& objectToFind)
	{
		TArray<uint32_t> returnArray;
		for (uint32_t i = 0; i < this->count; i++)
		{
			if (data[i] == objectToFind)
			{
				returnArray.Append(i);
			}
		}
		return returnArray;
	}

	TArray<uint32_t> FindAll(const T& objectToFind, uint32_t startIndex)
	{
		TArray<uint32_t> returnArray;
		for (uint32_t i = startIndex; i < this->count; i++)
		{
			if (data[i] == objectToFind)
			{
				returnArray.Append(i);
			}
		}
		return returnArray;
	}

	TArray<uint32_t> FindAll(std::function<bool(const T&)> findFunc)
	{
		TArray<uint32_t> returnArray;
		for (uint32_t i = 0; i < this->count; i++)
		{
			if (findFunc(data[i]))
			{
				returnArray.Append(i);
			}
		}
		return returnArray;
	}

	TArray<uint32_t> FindAll(std::function<bool(const T&)> findFunc, uint32_t startIndex)
	{
		TArray<uint32_t> returnArray;
		for (uint32_t i = startIndex; i < this->count; i++)
		{
			if (findFunc(data[i]))
			{
				returnArray.Append(i);
			}
		}
		return returnArray;
	}

	void Insert(T item, uint32_t index)
	{
		if (this->count >= this->capacity)
		{
			Grow();
		}
		for (int i = index; i < this->count; i++)
		{
			data[i + 1] = data[i];
		}
		data[index] = item;
		this->count++;
	}

	template<typename ... Args>
	T& EmplaceAppend(Args&& ... args)
	{
		if (this->count >= this->capacity)
		{
			Grow();
		}
		this->data[this->count] = T(std::forward<Args>(args) ...);
		this->count++;
		return this->data[this->count - 2];
	}

	template<typename ... Args>
	T& EmplaceAt(uint32_t index, Args&& ... args)
	{
		if (this->count >= this->capacity)
		{
			Grow();
		}
		for (int i = index; i < this->count; i++)
		{
			data[i + 1] = data[i];
		}
		data[index] = T(std::forward<Args>(args) ...);
		return data[index];
	}

	void Empty()
	{
		for (uint32_t i = 0; i < this->count; i++)
		{
			data[i].~T();
		}
		this->count = 0;
	}

	void Remove(const T& item)
	{
		bool found = false;
		for (int i = 0; i < this->count; i++)
		{
			if (data[i] == item)
			{
				found = true;
			}
			else if (found)
			{
				data[i - 1] = data[i];
			}
		}
	}

	void RemoveBack()
	{
		this->count--;
		this->data[this->count].~T();
	}

	void RemoveAt(uint32_t index)
	{
		for (int i = index + 1; i < this->count; i++)
		{
			data[i - 1] = data[i];
		}
	}

	void Swap(uint32_t indexA, uint32_t indexB)
	{
		T temp = data[indexA];
		data[indexA] = data[indexB];
		data[indexB] = temp;
	}
};
