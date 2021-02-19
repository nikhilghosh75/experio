#pragma once
#include "FFileCategory.h"

struct Filemask
{
	uint64_t mask;

	operator unsigned long long() { return mask; }

	Filemask()
	{
		this->mask = 0;
	}

	Filemask(uint64_t mask)
	{
		this->mask = mask;
	}

	bool CompareFile(uint8_t fileType) const
	{
		return (mask & (1 << fileType)) != 0;
	}

	bool CompareFile(FFileCategory category) const
	{
		return CompareFile((uint8_t)category.type);
	}

	void SetBitTrue(uint8_t bit)
	{
		this->mask = this->mask | (1 << bit);
	}

	void SetBitFalse(uint8_t bit)
	{
		this->mask = this->mask & (~(1 << bit));
	}

	void SetBitsTrue(uint8_t start = 0, uint8_t end = (uint8_t)EAssetType::Unknown)
	{
		for (uint8_t i = start; i < end; i++)
		{
			this->mask = this->mask | (1 << i);
		}
	}

	void SetBitsFalse(uint8_t start = 0, uint8_t end = (uint8_t)EAssetType::Unknown)
	{
		for (uint8_t i = start; i < end; i++)
		{
			this->mask = this->mask & (~(1 << i));
		}
	}

	static Filemask AND(Filemask f1, Filemask f2)
	{
		return Filemask(f1.mask & f2.mask);
	}

	// Change Name Later
	void FillBoolArray(bool* arr) const
	{
		for (uint8_t i = 0; i < 64; i++)
		{
			arr[i] = CompareFile(i);
		}
	}
};