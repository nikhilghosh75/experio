#include <cstdint>
#include "LPointerOperations.h"

void* LPointerOperations::Add(void* p, size_t x)
{
	return (void*)(reinterpret_cast<uintptr_t>(p) + x);
}