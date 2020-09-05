#include "TArray.h"
#include <iostream>
#include <exception>

void Test()
{
	TArray<int> array = *(new TArray<int>());

	// Initialize Array
	array.Init(125, 5);

	// Check Count
	std::cout << array.Count() << std::endl; // 5

	// Check Access Function
	array[3] = 6;
	std::cout << array[3] << std::endl; // 6
	std::cout << array[4] << std::endl; // 125

	// Check Object Append
	array.Append(64);

	// Check Array Append
	std::cout << array[5] << std::endl; // 64
	int tempArray[2];
	tempArray[0] = 12;
	tempArray[1] = 13;
	array.Append(tempArray, 2);
	std::cout << array[7] << std::endl; // 13

	// Check Array Insert
	array.Insert(256, 5);
	std::cout << array[5] << std::endl; // 256
	std::cout << array.Count() << std::endl; // 9

	// Check Array Insert (TArray)
	TArray<int> testArray = *(new TArray<int>());
	testArray.Init(343, 6);
	array.Insert(testArray, 6);
	std::cout << array.Count() << std::endl; // 15
	std::cout << array[10] << std::endl; // 343

	// Check Array Insert (Array)
	array.Insert(tempArray, 2, 10);
	std::cout << array[10] << std::endl; // 12

	// Check First
	std::cout << array.First() << std::endl; //125

	// Check Last
	std::cout << array.Last() << std::endl; // 13

	// Find
	std::cout << array.Find(6) << std::endl; // 3
	std::cout << array.Find(1) << std::endl; // -1

	// FindAll
	TArray<int> foundArray = array.FindAll(343);
	std::cout << foundArray.Count() << std::endl; // 6

	// FindInRange
	std::cout << array.FindInRange(343, 8, 12) << std::endl; // 8

	// RemoveAt
	array.RemoveAt(3);
	std::cout << array[3] << std::endl; // 125
	std::cout << array.Count() << std::endl; // 16

	// RemoveAt (RANGE)
	array.RemoveAt(13, 2);
	std::cout << array.Count() << std::endl; //14
	
	// RemoveSingle
	array.RemoveSingle(343);
	std::cout << array.FindAll(343).Count() << std::endl; // 5

	// RemoveInRange
	array.RemoveInRange(343, 4, 7);
	std::cout << array.FindAll(343).Count() << std::endl; // 3

	// Remove
	array.Remove(343);
	std::cout << array.FindAll(343).Count() << std::endl; // 0

	// Swap
	array.Swap(0, 7);
	std::cout << array[0] << std::endl; // 13

	// Plus
	//array += testArray;
	//cout << array.Count() << endl;
}

template <class T> 
TElement<T>::TElement()
{
    next = nullptr;
    previous = nullptr;
	this->count;
}

template<class T>
TElement<T>::TElement(T elements[], int count, TElement<T>* previous, TElement<T>* next)
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

template<class T>
TElement<T>::TElement(T elem1, T elem2, T elem3, T elem4, TElement<T>* previous, TElement<T>* next)
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

template<class T>
TElement<T>::TElement(T elem, int count, TElement<T>* previous, TElement<T>* next)
{
	this->previous = previous;
	this->next = next;
	data = new T[count];
	for(int i = 0; i < count; i++)
	{
		data[i] = elem;
	}
	this->count = count;
}

template<class T>
void TElement<T>::SetNext(TElement<T>* newNext)
{
	this->next = newNext;
}

template<class T>
int TElement<T>::Count()
{
	return this->count;
}

template<class T>
void TElement<T>::RemoveAt(int index)
{
	if(this->count == 0)
	{
		return;
	}

	T* newData = new T[this->count - 1];
	for(int i = 0; i < this->count; i++)
	{
		if(i < index)
		{
			newData[i] = this->data[i];
		}
		else if(i > index)
		{
			newData[i - 1] = this->data[i];
		}
	}
	this->count--;
	this->data = newData;
}

template<class T>
TArray<T>::TArray()
{
	start = new TElement<T>();
	end = start;
	numElements = 0;
	count = 0;
}

template<class T>
void TArray<T>::Init(T object, int num)
{
	TElement<T>* previous = nullptr;
	for(int i = 0; i < num/4; i++)
	{
		TElement<T>* tempElement = new TElement<T>(object, 4, previous, nullptr);
		if(previous != nullptr)
		{
			previous->SetNext(tempElement);
		}
		if(i == 0)
		{
			this->start = tempElement;
		}
		previous = tempElement;
		this->numElements++;
		this->count += 4;
	}

	if(num % 4 != 0)
	{
		this->end = new TElement<T>(object, num % 4, previous, nullptr);
		previous->SetNext(this->end);
		this->numElements++;
		this->count += num % 4;
	}
}

template<class T>
int TArray<T>::Num() const
{
	return numElements;
}

template<class T>
int TArray<T>::Count() const
{
	return count;
}

template<class T>
size_t TArray<T>::GetSize() const
{
	return count * sizeof(T);
}

template<class T>
bool TArray<T>::IsValidIndex(int index) const
{
	if(index < 0)
	{
		return false;
	}
	if(index >= count)
	{
		return false;
	}
	return true;
}

template<class T>
T& TArray<T>::operator[](int i)
{
	if(i > count)
	{
		// TO-DO: Add Error
	}

	int currentIndex = 0;
	TElement<T>* currentElement = start;
	while(currentElement->Count() + currentIndex <= i)
	{
		currentIndex += currentElement->Count();
		currentElement = currentElement->next;
	}
	return (currentElement->data[i - currentIndex]);
}

template<class T>
T& TArray<T>::First()
{
	return start->data[0];
}

template<class T>
T& TArray<T>::Last()
{
	return end->data[end->count - 1];
}

template<class T>
void TArray<T>::Append(const T object)
{
	if(count % 4 == 0)
	{
		TElement<T>* tempElement = new TElement<T>(object, 1, this->end, nullptr);
		this->end->next = tempElement;
		this->end = tempElement;
	}
	else
	{
		int oldElementCount = this->end->count;
		T* oldData = this->end->data;
		T* newData = new T[oldElementCount + 1];

		for(int i = 0; i < oldElementCount; i++)
		{
			newData[i] = oldData[i];
		}
		newData[oldElementCount] = object;
		this->end->data = newData;
		this->end->count++;
	}
	this->count++;
}

template <class T>
void TArray<T>::Append(const T objects[], int count)
{
	for(int i = 0; i < count; i++)
	{
		Append(objects[i]);
	}
}

template <class T>
void TArray<T>::Append(const TArray<T> objects)
{
	Append(objects.ToArray(), objects.count);
}

template<class T>
void TArray<T>::Insert(T object, int index)
{
	int currentIndex = 0;
	TElement<T>* currentElement = start;
	while(currentElement->Count() + currentIndex <= index)
	{
		currentIndex += currentElement->Count();
		currentElement = currentElement->next;
	}
	
	int oldElementCount = currentElement->count;
	T* oldData = currentElement->data;
	T* newData = new T[oldElementCount + 1];

	int i = 0;
	for(; i < index - currentIndex; i++)
	{
		newData[i] = oldData[i];
	}
	newData[i] = object;
	i++;
	for(; i < oldElementCount + 1; i++)
	{
		newData[i] = oldData[i - 1];
	}

	currentElement->data = newData;
	currentElement->count++;
	count++;
}

template<class T>
void TArray<T>::Insert(TArray<T> objects, int index)
{
	for(int i = 0; i < objects.Count(); i++)
	{
		Insert(objects[i], index + i);
	}
}

template<class T>
void TArray<T>::Insert(T objects[], int count, int index)
{
	for(int i = 0; i < count; i++)
	{
		Insert(objects[i], i + index);
	}
}

template<class T>
int TArray<T>::Find(T objectToFind)
{
	int currentIndex = 0;
	TElement<T>* currentElement = start;
	
	while(currentElement != nullptr)
	{
		for(int i = 0; i < currentElement->count; i++)
		{
			if(currentElement->data[i] == objectToFind)
			{
				return i + currentIndex;
			}
		}
		currentIndex += currentElement->Count();
		currentElement = currentElement->next;
	}

	return -1;
}

template<class T>
bool TArray<T>::Find(T objectToFind, int& indexOfObject)
{
	int foundIndex = Find(objectToFind);
	if(foundIndex == -1)
	{
		return false;
	}
	indexOfObject = foundIndex;
	return true;
}

template<class T>
TArray<int> TArray<T>::FindAll(T objectToFind)
{
	int currentIndex = 0;
	TElement<T>* currentElement = start;
	TArray<int> foundArray = *(new TArray<int>());

	while(currentElement != nullptr)
	{
		for(int i = 0; i < currentElement->count; i++)
		{
			if(currentElement->data[i] == objectToFind)
			{
				foundArray.Append(i + currentIndex);
			}
		}
		currentIndex += currentElement->Count();
		currentElement = currentElement->next;
	}

	return foundArray;
}

template<class T>
int TArray<T>::FindInRange(T objectToFind, int start, int end)
{
	int currentIndex = 0;
	TElement<T>* currentElement = this->start;
	
	while(currentElement != nullptr)
	{
		if(currentIndex + currentElement->count > start && currentIndex < end)
		{
			for(int i = 0; i < currentElement->count; i++)
			{
				if(i + currentIndex < start || i + currentIndex > end)
				{
					continue;
				}
				if(currentElement->data[i] == objectToFind)
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

template<class T>
bool TArray<T>::FindInRange(T objectToFind, int& indexOfObject, int start, int end)
{
	int foundIndex = this->FindInRange(objectToFind, start, end);
	if(foundIndex == -1)
	{
		return false;
	}
	indexOfObject = foundIndex;
	return true;
}

template<class T>
TArray<int> TArray<T>::FindAllInRange(T objectToFind, int start, int end)
{
	int currentIndex = 0;
	TElement<T>* currentElement = this->start;
	TArray<T> foundArray = *(new TArray<T>());
	
	while(currentElement != nullptr)
	{
		if(currentIndex + currentElement->count > start && currentIndex < end)
		{
			for(int i = 0; i < currentElement->count; i++)
			{
				if(i + currentIndex < start || i + currentIndex > end)
				{
					continue;
				}
				if(currentElement->data[i] == objectToFind)
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

template<class T>
bool TArray<T>::AddUnique(T object)
{
	if(Find(object) == -1)
	{
		Append(object);
		return true;
	}
	return false;
}

template<class T>
void TArray<T>::Empty()
{
	this->count = 0;
	this->start = new TElement<T>();
	this->end = this->start;
	this->numElements = 0;
}

template<class T>
void TArray<T>::Remove(T item)
{
	int currentIndex = 0;
	TElement<T>* currentElement = this->start;
	
	while(currentElement != nullptr)
	{
		for(int i = currentElement->count; i >= 0; i--)
		{
			if(currentElement->data[i] == item)
			{
				currentElement->RemoveAt(i);
				this->count--;
			}
		}
		currentIndex += currentElement->Count();
		currentElement = currentElement->next;
	}
}

template <class T>
void TArray<T>::RemoveInRange(T item, int start, int end)
{
	int currentIndex = 0;
	TElement<T>* currentElement = this->start;
	
	while(currentElement != nullptr)
	{
		if(currentIndex + currentElement->count > start && currentIndex < end)
		{
			for(int i = currentElement->count; i >= 0; i--)
			{
				if(i + currentIndex < start || i + currentIndex > end)
				{
					continue;
				}
				if(currentElement->data[i] == item)
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

template<class T>
void TArray<T>::RemoveAt(int index)
{
	int currentIndex = 0;
	TElement<T>* currentElement = this->start;
	
	while(currentElement->Count() + currentIndex <= index)
	{
		currentIndex += currentElement->Count();
		currentElement = currentElement->next;
	}
	currentElement->RemoveAt(index - currentIndex);
	this->count--;
}

template<class T>
void TArray<T>::RemoveAt(int index, int count)
{
	int end = index + count - 1;

	int currentIndex = 0;
	TElement<T>* currentElement = this->start;
	
	while(currentElement != nullptr)
	{
		if(currentIndex + currentElement->count > index && currentIndex < end)
		{
			for(int i = currentElement->count; i >= 0; i--)
			{
				if(i + currentIndex < index || i + currentIndex > end)
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

template <class T>
void TArray<T>::RemoveSingle(T item)
{
	int currentIndex = 0;
	TElement<T>* currentElement = this->start;
	
	while(currentElement != nullptr)
	{
		for(int i = 0; i < currentElement->count; i++)
		{
			if(currentElement->data[i] == item)
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

template <class T>
T* TArray<T>::ToArray() const
{
	T elements[this->count];
	int currentIndex = 0;
	TElement<T>* currentElement = this->start;
	
	while(currentElement != nullptr)
	{
		for(int i = 0; i < currentElement->count; i++)
		{
			elements[currentIndex + i] = currentElement->data[i];
		}
		currentIndex += currentElement->Count();
		currentElement = currentElement->next;
	}
}

template <class T>
std::string TArray<T>::ToString() const
{
	std::string s = "";
	int currentIndex = 0;
	TElement<T>* currentElement = this->start;

	std::stringstream ss;
	std::string tempString;

	while(currentElement != nullptr)
	{
		for(int i = 0; i < currentElement->count; i++)
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

template <class T>
void TArray<T>::Swap(int indexA, int indexB)
{
	TElement<T>* elementA = nullptr;
	TElement<T>* elementB = nullptr;
	int elementIndexA = 0;
	int elementIndexB = 0;

	int currentIndex = 0;
	TElement<T>* currentElement = this->start;

	while(currentElement != nullptr)
	{
		if(currentIndex <= indexA && currentIndex + currentElement->Count() > indexA)
		{
			elementA = currentElement;
			elementIndexA = indexA - currentIndex;
		}
		if(currentIndex <= indexB && currentIndex + currentElement->Count() > indexB)
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

/*
template <class T>
TArray<T> TArray<T>::operator+(const TArray<T> array)
{
	Append(array);
	return *this;
}

template <class T>
TArray<T> TArray<T>::operator+(const T item)
{
	Append(item);
	return *this;
}

template <class T>
TArray<T> TArray<T>::operator+=(const TArray<T> array)
{
	Append(array);
	return *this;
}

template <class T>
TArray<T> TArray<T>::operator+=(const T item)
{
	Append(item);
	return *this;
}
*/