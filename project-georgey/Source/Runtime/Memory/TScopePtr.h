#pragma once

template<class T>
class TScopedPtr
{
	T* ptr;
public:
	TScopedPtr(T* ptr = nullptr)
	{
		this->ptr = ptr;
	}

	~TScopedPtr()
	{
		delete ptr;
	}

	T& operator*() { return *ptr; }
	const T& operator*() { return *ptr; }

	T* operator->() { return ptr; }
	const T* operator->() { return ptr; }
};