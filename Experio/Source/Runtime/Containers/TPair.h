#pragma once

/// <summary>
/// A templated class representing a pair of two values
/// </summary>

template<typename T1, typename T2>
class TPair
{
public:
	T1 first;
	T2 second;

	TPair()
	{
		this->first = T1();
		this->second = T2();
	}

	TPair(const T1& first, const T2& second)
	{
		this->first = first;
		this->second = second;
	}

	bool operator==(const TPair<T1, T2>& other)
	{
		return this->first == other.first && this->second == other.second;
	}

	bool operator!=(const TPair<T1, T2>& other)
	{
		return this->first != other.first || this->second != other.second;
	}
};