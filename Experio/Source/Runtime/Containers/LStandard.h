#pragma once

// NOTE: This will be deleted later once TArray and TList are created
// This is just temporary.

// Used for Standard Containers

#include <vector>

class LStandard
{
public:
	template<typename T>
	static bool ExistsInVector(const std::vector<T>& vector, const T& object)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] == object)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>	
	static bool ExistsInVector(const std::vector<T*>& vector, const T* object)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] == object)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	static void RemoveElement(std::vector<T>& vector, const T& object)
	{
		bool found = false;
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] == object)
			{
				found = true;
			}
			else if (found)
			{
				vector[i - 1] = vector[i];
			}
		}
		vector.pop_back();
	}

	template<typename T>
	static void RemoveElement(std::vector<T*>& vector, const T* object)
	{
		bool found = false;
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] == object)
			{
				found = true;
			}
			else if (found)
			{
				vector[i - 1] = vector[i];
			}
		}
		vector.pop_back();
	}
};