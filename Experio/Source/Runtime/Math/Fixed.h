#pragma once
#include <stdint.h>
#include "LMath.h"

template<size_t I>
class IntOfSize
{
	static constexpr bool is_specialized = false;

	using ValueType = int;
	using UnsignedType = unsigned int;

	static const UnsignedType MaxUnsigned = 4294967295;
};

template<> class IntOfSize<8>
{
	static constexpr bool is_specialized = true;

	using ValueType = int8_t;
	using UnsignedType = uint8_t;

	static const UnsignedType MaxUnsigned = 255;
};

template<> class IntOfSize<16>
{
	static constexpr bool is_specialized = true;

	using ValueType = int16_t;
	using UnsignedType = uint16_t;

	static const UnsignedType MaxUnsigned = 65535;
};

template<> class IntOfSize<32>
{
	static constexpr bool is_specialized = true;

	using ValueType = int32_t;
	using UnsignedType = uint32_t;

	static const UnsignedType MaxUnsigned = 4294967295;
};

template<> class IntOfSize<64>
{
	static constexpr bool is_specialized = true;

	using ValueType = int64_t;
	using UnsignedType = uint64_t;

	static const UnsignedType MaxUnsigned = 18446744073709551615;
};

template<size_t I, size_t F>
class FixedBase
{
	using IntegerType = IntOfSize<I>::ValueType;
	using FractionType = IntOfSize<F>::UnsignedType;

public:
	IntegerType integer;
	FractionType fraction;

	static const FixedBase Epsilon(0, 1);

	FixedBase()
	{
		this->integer = 0;
		this->fraction = 0;
	}

	FixedBase(IntegerType integer, FractionType fraction)
	{
		this->integer = integer;
		this->fraction = fraction;
	}

	FixedBase(const FixedBase& other) = default;

	FixedBase(int i)
	{
		this->integer = i;
		this->fraction = 0;
	}

	// (8-bit): 14.945 == {14, 242}
	FixedBase(float f)
	{
		this->integer = (IntegerType)f;
		this->fraction = LMath::FMod(f, 1) * IntOfSize<F>::MaxUnsigned;
	}

	FixedBase(double d)
	{
		this->integer = (IntegerType)d;
		this->fraction = LMath::FMod((float)d, 1) * IntOfSize<F>::MaxUnsigned;
	}

	float operator()
	{
		return (float)this->integer + (float)this->fraction / (float)IntOfSize<F>::MaxUnsigned;
	}

	double operator()
	{
		return (double)this->integer + (double)this->fraction / (double)IntOfSize<F>::MaxUnsigned;
	}

	FixedBase<I, F> operator-() const
	{
		return FixedBase(-this->integer, this->fraction);
	}

	FixedBase<I, F> operator+() const
	{
		return FixedBase(+this->integer, this->fraction);
	}

	FixedBase<I, F> operator+(const FixedBase<I, F>& other)
	{
		int overflow = 0;
		if (this->fraction > IntOfSize<F>::MaxUnsigned - other.fraction)
		{
			overflow = 1;
		}
		return FixedBase(this->integer + other.integer + overflow, this->fraction + other.fraction);
	}

	FixedBase<I, F> operator-(const FixedBase<I, F>& other)
	{
		int underflow = 0;
		if (this->fraction < other.fraction)
		{
			underflow = 1;
		}
		return FixedBase(this->integer - other.integer - underflow, this->fraction - other.fraction);
	}

	FixedBase<I, F> operator*(const FixedBase<I, F>& other)
	{
		
	}

	FixedBase<I, F> operator/(const FixedBase<I, F>& other)
	{

	}

	bool operator==(const FixedBase<I, F>& other) const
	{
		return this->integer == other.integer && this->fraction == other.fraction;
	}

	bool operator!=(const FixedBase<I, F>& other) const
	{
		return this->integer != other.integer || this->fraction != other.fraction;
	}

	bool operator>(const FixedBase<I, F>& other) const
	{
		if (this->integer == other.integer)
		{
			if (this->integer < 0)
			{
				return this->fraction < other.fraction;
			}
			return this->fraction > other.fraction;
		}
		return this->integer > other.integer;
	}

	bool operator<(const FixedBase<I, F>& other) const
	{
		if (this->integer == other.integer)
		{
			if (this->integer < 0)
			{
				return this->fraction > other.fraction;
			}
			return this->fraction < other.fraction;
		}
		return this->integer < other.integer;
	}
};

using FixedHalf = FixedBase<8, 8>;
using Fixed = FixedBase<16, 16>;
using FixedDouble = FixedBase<32, 32>;
