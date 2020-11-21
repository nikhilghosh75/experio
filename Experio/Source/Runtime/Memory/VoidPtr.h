#pragma once

#include <stdint.h>

class VoidPtr
{
public:
	void* ptr;

	VoidPtr()
	{
		this->ptr = nullptr;
	}

	VoidPtr(void* ptr)
	{
		this->ptr = ptr;
	}

	VoidPtr(const VoidPtr& other)
	{
		this->ptr = ptr;
	}

	operator void*() const
	{
		return this->ptr;
	}

	operator char*() const
	{
		return (char*)this->ptr;
	}

	VoidPtr& operator+(const VoidPtr& other)
	{
		return VoidPtr((char*)this->ptr + (uint32_t)other.ptr);
	}

	VoidPtr& operator+(size_t n)
	{
		return VoidPtr((char*)this->ptr + n);
	}

	VoidPtr& operator+(void* other)
	{
		return VoidPtr((char*)this->ptr + (uint32_t)other);
	}

	VoidPtr& operator-(const VoidPtr& other)
	{
		return VoidPtr((char*)this->ptr - (uint32_t)other.ptr);
	}

	VoidPtr& operator-(size_t n)
	{
		return VoidPtr((char*)this->ptr - n);
	}

	VoidPtr& operator-(void* other)
	{
		return VoidPtr((char*)this->ptr - (uint32_t)other);
	}

	VoidPtr& operator+=(const VoidPtr& other)
	{
		*this = VoidPtr((char*)this->ptr + (uint32_t)other.ptr);
		return *this;
	}

	VoidPtr& operator+=(size_t n)
	{
		*this = VoidPtr((char*)this->ptr + n);
		return *this;
	}

	VoidPtr& operator+=(void* other)
	{
		*this = VoidPtr((char*)this->ptr + (uint32_t)other);
		return *this;
	}

	VoidPtr& operator-=(const VoidPtr& other)
	{
		*this = VoidPtr((char*)this->ptr - (uint32_t)other.ptr);
		return *this;
	}

	VoidPtr& operator-=(size_t n)
	{
		*this = VoidPtr((char*)this->ptr - n);
		return *this;
	}

	VoidPtr& operator-=(void* other)
	{
		*this = VoidPtr((char*)this->ptr - (uint32_t)other);
		return *this;
	}

	VoidPtr& operator++()
	{
		this->ptr = (char*)this->ptr + 1;
		return *this;
	}

	VoidPtr& operator++(int)
	{
		VoidPtr temp(this->ptr);
		++temp;
		return temp;
	}

	VoidPtr& operator--()
	{
		this->ptr = (char*)this->ptr - 1;
		return *this;
	}

	VoidPtr& operator--(int)
	{
		VoidPtr temp(this->ptr);
		--temp;
		return temp;
	}

	bool operator==(const VoidPtr& other) const
	{
		return this->ptr == other.ptr;
	}

	bool operator==(const void* other) const
	{
		return this->ptr == other;
	}

	bool operator!=(const VoidPtr& other) const
	{
		return this->ptr != other.ptr;
	}

	bool operator!=(const void* other) const
	{
		return this->ptr != other;
	}

	bool operator<(const VoidPtr& other) const
	{
		return this->ptr < other.ptr;
	}

	bool operator<(const void* other) const
	{
		return this->ptr < other;
	}

	bool operator>(const VoidPtr& other) const
	{
		return this->ptr > other.ptr;
	}

	bool operator>(const void* other) const
	{
		return this->ptr > other;
	}

	bool operator<=(const VoidPtr& other) const
	{
		return this->ptr <= other.ptr;
	}

	bool operator<=(const void* other) const
	{
		return this->ptr <= other;
	}

	bool operator>=(const VoidPtr& other) const
	{
		return this->ptr >= other.ptr;
	}

	bool operator>=(const void* other) const
	{
		return this->ptr >= other;
	}
};

void TestVoidPtr()
{
	VoidPtr voidPtr = VoidPtr((void*)204);
	voidPtr = voidPtr + 5;
	char* str = voidPtr;
}