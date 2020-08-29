#pragma once
#include <stdint.h>
#include "GameObject.h"

struct Layermask
{
	uint64_t mask;

	operator unsigned long long() { return mask; }

	Layermask(uint64_t mask)
	{
		this->mask = mask;
	}

	bool CompareLayer(uint8_t layer)
	{
		return (mask & (1 << layer)) != 0;
	}

	bool CompareLayer(GameObject object)
	{
		return CompareLayer(object.layer);
	}

	static Layermask AND(Layermask L1, Layermask L2)
	{
		return Layermask(L1.mask & L2.mask);
	}
};