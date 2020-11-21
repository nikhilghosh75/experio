#pragma once
#include <string>

template<typename T>
class TUnrolledElement
{
public:
	T * data;
	TUnrolledElement<T>* previous;
	TUnrolledElement<T>* next;
	int count;

	TUnrolledElement()
	{
		next = nullptr;
		previous = nullptr;
		this->count;
	}

	TUnrolledElement(T elements[], int count, TUnrolledElement<T>* previous, TUnrolledElement<T>* next)
	{
		this->previous = previous;
		this->next = next;
		data = new T[count];
		for (int i = 0; i < count; i++)
		{
			data[i] = elements[i];
		}
		this->count = count;
	}

	TUnrolledElement(T elem1, T elem2, T elem3, T elem4, TUnrolledElement<T>* previous, TUnrolledElement<T>* next)
	{
		this->previous = previous;
		this->next = next;
		data = new T[4];
		data[0] = elem1;
		data[1] = elem2;
		data[2] = elem3;
		data[3] = elem4;
		this->count = 4;
	}

	TUnrolledElement(T elem, int count, TUnrolledElement<T>* previous, TUnrolledElement<T>* next)
	{
		this->previous = previous;
		this->next = next;
		data = new T[count];
		for (int i = 0; i < count; i++)
		{
			data[i] = elem;
		}
		this->count = count;
	}

	~TUnrolledElement()
	{
		delete this->data;
	}

	void SetNext(TUnrolledElement<T>* newNext) 
	{
		this->next = newNext;
	}

	int Count() { return this->count; }
	T* Get(int i) { return data[i]; } // Potentially add assertion to check

	void RemoveAt(int index)
	{
		if (this->count == 0)
		{
			return;
		}

		T* newData = new T[this->count - 1];
		for (int i = 0; i < this->count; i++)
		{
			if (i < index)
			{
				newData[i] = this->data[i];
			}
			else if (i > index)
			{
				newData[i - 1] = this->data[i];
			}
		}
		this->count--;
		this->data = newData;
	}
};

template<typename T>
class TUnrolledList
{
private:
	TUnrolledElement<T>* start;
	TUnrolledElement<T>* end;
	int numElements;
	int count;
public:
	TUnrolledList()
	{
		start = new TUnrolledElement<T>();
		end = start;
		numElements = 0;
		count = 0;
	}

	TUnrolledList(T object, int num)
	{
		this->start = new TUnrolledElement<T>();
		TUnrolledElement<T>* previous = nullptr;

		for (int i = 0; i < num / 4; i++)
		{
			TUnrolledElement<T>* tempElement = new TUnrolledElement<T>(object, 4, previous, nullptr);
			if (previous != nullptr)
			{
				previous->SetNext(tempElement);
			}
			if (i == 0)
			{
				this->start = tempElement;
			}
			previous = tempElement;
			this->numElements++;
			this->count += 4;
		}

		if (num % 4 != 0)
		{
			this->end = new TUnrolledElement<T>(object, num % 4, previous, nullptr);
			previous->SetNext(this->end);
			this->numElements++;
			this->count += num % 4;
		}
	}

	TUnrolledList(T* objects, int num)
	{
		// Add stuff here
	}

	void Append(const T object)
	{
		if (count % 4 == 0)
		{
			TUnrolledElement<T>* tempElement = new TUnrolledElement<T>(object, 1, this->end, nullptr);
			this->end->next = tempElement;
			this->end = tempElement;
			this->numElements++;
		}
		else
		{
			int oldElementCount = this->end->count;
			T* oldData = this->end->data;
			T* newData = new T[oldElementCount + 1];

			for (int i = 0; i < oldElementCount; i++)
			{
				newData[i] = oldData[i];
			}
			newData[oldElementCount] = object;
			this->end->data = newData;
			this->end->count++;
		}
		this->count++;
	}

	void Append(const T objects[], int count)
	{
		for (int i = 0; i < count; i++)
		{
			Append(objects[i]);
		}
	}

	void Append(const TUnrolledList<T> objects)
	{
		Append(objects.ToArray(), objects.count);
	}

	void Insert(T object, int index)
	{
		int currentIndex = 0;
		TElement<T>* currentElement = start;
		while (currentElement->Count() + currentIndex <= index)
		{
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}

		int oldElementCount = currentElement->count;
		T* oldData = currentElement->data;
		T* newData = new T[oldElementCount + 1];

		int i = 0;
		for (; i < index - currentIndex; i++)
		{
			newData[i] = oldData[i];
		}
		newData[i] = object;
		i++;
		for (; i < oldElementCount + 1; i++)
		{
			newData[i] = oldData[i - 1];
		}

		currentElement->data = newData;
		currentElement->count++;
		count++;
	}

	void Insert(TUnrolledList<T> objects, int index)
	{
		for (int i = 0; i < objects.Count(); i++)
		{
			Insert(objects[i], index + i);
		}
	}

	void Insert(T objects[], int count, int index)
	{
		for (int i = 0; i < count; i++)
		{
			Insert(objects[i], i + index);
		}
	}

	int Num() const { return numElements; }
	int Count() const { return count; }
	size_t GetSize() const { return count * sizeof(T); }
	bool IsValidIndex(int index) const
	{
		return index >= 0 && index < count;
	}

	T& operator[](int i)
	{
		if (i > count)
		{
			// TO-DO: Add Error
		}

		int currentIndex = 0;
		TElement<T>* currentElement = start;
		while (currentElement->Count() + currentIndex <= i)
		{
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}
		return (currentElement->data[i - currentIndex]);
	}

	T& First()
	{
		return start->data[0];
	}

	T& Last()
	{
		return end->data[end->count - 1];
	}

	int Find(T objectToFind)
	{
		int currentIndex = 0;
		TElement<T>* currentElement = start;

		while (currentElement != nullptr)
		{
			for (int i = 0; i < currentElement->count; i++)
			{
				if (currentElement->data[i] == objectToFind)
				{
					return i + currentIndex;
				}
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}

		return -1;
	}

	bool Find(T objectToFind, int& indexOfObject)
	{
		int foundIndex = Find(objectToFind);
		if (foundIndex == -1)
		{
			return false;
		}
		indexOfObject = foundIndex;
		return true;
	}

	TUnrolledList<int> FindAll(T objectToFind)
	{
		int currentIndex = 0;
		TUnrolledElement<T>* currentElement = start;
		TUnrolledList<int> foundArray = TUnrolledList<int>();

		while (currentElement != nullptr)
		{
			for (int i = 0; i < currentElement->count; i++)
			{
				if (currentElement->data[i] == objectToFind)
				{
					foundArray.Append(i + currentIndex);
				}
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}

		return foundArray;
	}

	int FindInRange(T objectToFind, int start, int end)
	{
		int currentIndex = 0;
		TElement<T>* currentElement = this->start;

		while (currentElement != nullptr)
		{
			if (currentIndex + currentElement->count > start && currentIndex < end)
			{
				for (int i = 0; i < currentElement->count; i++)
				{
					if (i + currentIndex < start || i + currentIndex > end)
					{
						continue;
					}
					if (currentElement->data[i] == objectToFind)
					{
						return i + currentIndex;
					}
				}
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}

		return -1;
	}

	bool FindInRange(T objectToFind, int& indexOfObject, int start, int end)
	{
		int foundIndex = this->FindInRange(objectToFind, start, end);
		if (foundIndex == -1)
		{
			return false;
		}
		indexOfObject = foundIndex;
		return true;
	}

	TUnrolledList<int> FindAllInRange(T objectToFind, int start, int end)
	{
		int currentIndex = 0;
		TElement<T>* currentElement = this->start;
		TArray<T> foundArray = *(new TArray<T>());

		while (currentElement != nullptr)
		{
			if (currentIndex + currentElement->count > start && currentIndex < end)
			{
				for (int i = 0; i < currentElement->count; i++)
				{
					if (i + currentIndex < start || i + currentIndex > end)
					{
						continue;
					}
					if (currentElement->data[i] == objectToFind)
					{
						foundArray.Append(i + currentIndex);
					}
				}
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}

		return foundArray;
	}

	bool AddUnique(T object)
	{
		if (Find(object) == -1)
		{
			Append(object);
			return true;
		}
		return false;
	}

	void Empty()
	{
		this->count = 0;
		TUnrolledElement<T>* current = this->start;
		while (current != nullptr)
		{
			TUnrolledElement<T>* temp = current;
			current = current->next;
			delete temp;
		}
		this->numElements = 0;
	}

	void Remove(T item)
	{
		int currentIndex = 0;
		TElement<T>* currentElement = this->start;

		while (currentElement != nullptr)
		{
			for (int i = currentElement->count; i >= 0; i--)
			{
				if (currentElement->data[i] == item)
				{
					currentElement->RemoveAt(i);
					this->count--;
				}
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}
	}

	void RemoveInRange(T item, int start, int end)
	{
		int currentIndex = 0;
		TElement<T>* currentElement = this->start;

		while (currentElement != nullptr)
		{
			if (currentIndex + currentElement->count > start && currentIndex < end)
			{
				for (int i = currentElement->count; i >= 0; i--)
				{
					if (i + currentIndex < start || i + currentIndex > end)
					{
						continue;
					}
					if (currentElement->data[i] == item)
					{
						currentElement->RemoveAt(i);
						this->count--;
					}
				}
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}
	}

	void RemoveAt(int index)
	{
		int currentIndex = 0;
		TElement<T>* currentElement = this->start;

		while (currentElement->Count() + currentIndex <= index)
		{
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}
		currentElement->RemoveAt(index - currentIndex);
		this->count--;
	}

	void RemoveAt(int index, int count)
	{
		int end = index + count - 1;

		int currentIndex = 0;
		TElement<T>* currentElement = this->start;

		while (currentElement != nullptr)
		{
			if (currentIndex + currentElement->count > index && currentIndex < end)
			{
				for (int i = currentElement->count; i >= 0; i--)
				{
					if (i + currentIndex < index || i + currentIndex > end)
					{
						continue;
					}
					currentElement->RemoveAt(i);
					this->count--;
				}
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}
	}

	void RemoveSingle(T item)
	{
		int currentIndex = 0;
		TElement<T>* currentElement = this->start;

		while (currentElement != nullptr)
		{
			for (int i = 0; i < currentElement->count; i++)
			{
				if (currentElement->data[i] == item)
				{
					currentElement->RemoveAt(i);
					this->count--;
					return;
				}
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}
	}

	T* ToArray() const
	{
		T elements[this->count];
		int currentIndex = 0;
		TElement<T>* currentElement = this->start;

		while (currentElement != nullptr)
		{
			for (int i = 0; i < currentElement->count; i++)
			{
				elements[currentIndex + i] = currentElement->data[i];
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}
	}

	std::string ToString() const
	{
		std::string s = "";
		int currentIndex = 0;
		TElement<T>* currentElement = this->start;

		std::stringstream ss;
		std::string tempString;

		while (currentElement != nullptr)
		{
			for (int i = 0; i < currentElement->count; i++)
			{
				ss << currentElement->data[i];
				ss >> tempString;
				s += tempString + " ";
				ss.clear();
			}
			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}
		return s;
	}

	void Swap(int indexA, int indexB)
	{
		TElement<T>* elementA = nullptr;
		TElement<T>* elementB = nullptr;
		int elementIndexA = 0;
		int elementIndexB = 0;

		int currentIndex = 0;
		TElement<T>* currentElement = this->start;

		while (currentElement != nullptr)
		{
			if (currentIndex <= indexA && currentIndex + currentElement->Count() > indexA)
			{
				elementA = currentElement;
				elementIndexA = indexA - currentIndex;
			}
			if (currentIndex <= indexB && currentIndex + currentElement->Count() > indexB)
			{
				elementB = currentElement;
				elementIndexB = indexB - currentIndex;
			}

			currentIndex += currentElement->Count();
			currentElement = currentElement->next;
		}

		T tempData = elementA->data[elementIndexA];
		elementA->data[elementIndexA] = elementB->data[elementIndexB];
		elementB->data[elementIndexB] = tempData;
	}

	operator std::string() const { return ToString(); }

	TUnrolledList<T> operator+(const TUnrolledList<T> array)
	{
		Append(array);
		return *this;
	}

	TUnrolledList<T> operator+(const T item)
	{
		Append(array);
		return *this;
	}

	TUnrolledList<T> operator+=(const TUnrolledList<T> array)
	{
		Append(array);
		return *this;
	}

	TUnrolledList<T> operator+=(const T& item)
	{
		Append(item);
		return *this;
	}
};