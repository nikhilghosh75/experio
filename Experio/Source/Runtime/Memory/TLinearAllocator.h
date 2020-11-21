#pragma once
#include "TAllocator.h"

template <class T> 
class TLinearAllocator : public TAllocator<T>
{
public:
    TLinearAllocator();
    TLinearAllocator(size_t size);
    TLinearAllocator(size_t size, void* start);
    ~TLinearAllocator();

    void* Allocate(size_t size, uint8_t alignment) override;
    void Deallocate(void* p) override;
    void Init() override;
    void Clear();

private:
    void* currentPosition;
    size_t offset;
};