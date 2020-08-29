#include <exception>
#include <stdexcept>
#include "TAllocator.h"

template<class T>
TAllocator<T>::TAllocator()
{
	this->totalSize = sizeof(T);
	memoryUsed = 0;
	allocationsMade = 0;
    totalSize = 0;
}

template<class T>
TAllocator<T>::TAllocator(size_t totalSize)
{
    this->totalSize = totalSize;
    memoryUsed = 0;
    allocationsMade = 0;
}

template<class T>
TAllocator<T>::TAllocator(size_t size, void* start)
{
    this->start = start;
    this->totalSize = size;
    memoryUsed = 0;
    allocationsMade = 0;
}

/*
template<class T>
TAllocator<T>::~TAllocator()
{
	start = nullptr;
	totalSize = 0;
}
*/

template<class T>
void* TAllocator<T>::Allocate(size_t size, uint8_t alignment)
{

}

template<class T>
void TAllocator<T>::Deallocate(void* p)
{

}

template<class T>
void TAllocator<T>::Init()
{

}

template<class T>
void TAllocator<T>::Delete(T & object)
{
    object.~T();
    Deallocate(&object);
}

template<class T>
T* TAllocator<T>::AllocateArray(size_t length)
{
    if(length == 0)
    {
        //TO-DO: Error
    }

    uint8_t headerSize = sizeof(size_t)/sizeof(T);

    if(sizeof(size_t) % sizeof(T) > 0)
    {
        headerSize++;
    }

    T* pointer = ((T*) Allocate(sizeof(T) * (length + headerSize), __alignof(T))) + headerSize;
    *( ((size_t*)pointer) - 1 ) = length;

    for(size_t i = 0; i < length; i++)
    {
        new (&pointer) T;
    }
    return pointer;
}

template<class T>
void TAllocator<T>::DeallocateArray(T * array)
{
    if(array == nullptr)
    {
		throw std::invalid_argument("Array is null");
    }

    size_t length = *(((size_t*)array) - 1);

    for(size_t i = 0; i < length; i++)
    {
        array.~T();
    }

    uint8_t headerSize = sizeof(size_t)/sizeof(T);

    if(sizeof(size_t) % sizeof(T) > 0)
    {
        headerSize += 1;
    }

    Deallocate(array - headerSize);
}
