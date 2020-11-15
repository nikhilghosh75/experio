#pragma once

template<typename T1, typename T2>
class TPair
{
public:
	T1 first;
	T2 second;

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