#pragma once
#include <cstdint>
#include <exception>
using namespace std;

struct InvalidSizeException : public exception {
	size_t invalidSize;
	InvalidSizeException(size_t size)
	{
		invalidSize = size;
	}

	const char * what() const throw()
	{
		return invalidSize + " is not a valid size for an array or memory allocation";
	}
};

template <class T> 
class TAllocator
{
public:
	TAllocator();

    TAllocator(size_t totalSize);

    TAllocator(size_t size, void* start);

    //virtual ~TAllocator();

    virtual void* Allocate(size_t size, uint8_t alignment = 4);

    virtual void Deallocate(void* p);

    virtual void Init();

    //T* AllocateNew();
    //T* AllocateNew(const T& object);

    void Delete(T& object);

    T* AllocateArray(size_t length);

    void DeallocateArray(T* array);

protected:
    void* start; 
    size_t memoryUsed; 
    size_t allocationsMade;
    size_t totalSize;
};