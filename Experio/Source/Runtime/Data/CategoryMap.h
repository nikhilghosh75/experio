#pragma once
#include <functional>
#include <string>
#include <vector>
#include "../Containers/Algorithm.h"
#include "../Containers/LString.h"

template<typename T>
class CategoryMap
{
public:
	std::string categoryName;
	std::vector<CategoryMap<T>*> subcategories;
	std::vector<T> elements;
	
	CategoryMap()
	{
		categoryName = "";
	}

	CategoryMap(const std::string& category)
	{
		categoryName = category;
	}

	void Insert(const std::string& category, const T& elem, char delimiter = '/')
	{
		if (category.empty())
		{
			elements.push_back(elem);
			return;
		}
		else if (LString::NumOfChars(category, delimiter) == 0)
		{
			for (size_t i = 0; i < subcategories.size(); i++)
			{
				if (subcategories[i]->categoryName == category)
				{
					subcategories[i]->elements.push_back(elem);
					return;
				}
			}
			subcategories.push_back(new CategoryMap(category));
			subcategories.back()->elements.push_back(elem);
			return;
		}
		std::vector<std::string> categories = LString::SeperateStringByChar(category, delimiter);
		RecursiveInsert(categories, 0, elem);
	}

	size_t Count() const
	{
		size_t count = 0;
		for (size_t i = 0; i < subcategories.size(); i++)
		{
			count += subcategories[i]->Count();
		}
		count += elements.size();
		return count;
	}

	void ForEach(std::function<void(T&)> func)
	{
		for (size_t i = 0; i < subcategories.size(); i++)
		{
			subcategories[i]->ForEach(func);
		}

		for (size_t i = 0; i < elements.size(); i++)
		{
			func(elements[i]);
		}
	}

	/*
	void ForEach(std::function<void(T&)> func, std::function<void(const std::string&)> onCategoryEnter,
		std::function<void(const std::string&)> onCategoryExit)
	{
		onCategoryEnter(categoryName);
		for (size_t i = 0; i < subcategories.size(); i++)
		{
			subcategories[i]->ForEach(func);
		}

		for (size_t i = 0; i < elements.size(); i++)
		{
			func(elements[i]);
		}
		onCategoryExit(categoryName);
	}
	*/

	void ForEach(std::function<void(T&)> func, std::function<bool(const std::string&)> onCategoryEnter,
		std::function<void(const std::string&)> onCategoryExit)
	{
		if (!onCategoryEnter(categoryName))
			return;

		for (size_t i = 0; i < subcategories.size(); i++)
		{
			subcategories[i]->ForEach(func, onCategoryEnter, onCategoryExit);
		}

		for (size_t i = 0; i < elements.size(); i++)
		{
			func(elements[i]);
		}
		onCategoryExit(categoryName);
	}

	void Remove(const std::string& category, T& elem, char delimiter)
	{
		if (category.empty())
		{
			Experio::Algorithm::RemoveElement(subcategories, elem);
			return;
		}

		std::vector<std::string> categories = LString::SeperateStringByChar(category, delimiter);
		RecursiveRemove(categories, 0, elem);
	}

private:
	void RecursiveInsert(const std::vector<std::string>& categories, size_t currentIndex, const T& elem)
	{
		if (currentIndex >= categories.size())
		{
			elements.push_back(elem);
			return;
		}

		for (size_t i = 0; i < subcategories.size(); i++)
		{
			if (subcategories[i]->categoryName == categories[currentIndex])
			{
				RecursiveInsert(categories, currentIndex + 1, elem);
				return;
			}
		}
		
		subcategories.push_back(new CategoryMap(categories[currentIndex]));
		subcategories.back()->RecursiveInsert(categories, currentIndex + 1, elem);
	}

	void RecursiveRemove(const std::vector<std::string>& categories, size_t currentIndex, const T& elem)
	{
		if (currentIndex >= categories.size())
		{
			Experio::Algorithm::RemoveElement(subcategories, elem);
			return;
		}

		for (size_t i = 0; i < subcategories.size(); i++)
		{
			if (subcategories[i]->categoryName == categories[currentIndex])
			{
				RecursiveInsert(categories, currentIndex + 1, elem);
				return;
			}
		}
	}
};