#pragma once

// Note that this is Experio code that interfaces with Toml Types

#include "toml.h"

#include "../../Runtime/Time/FDateTime.h"

void DateTimeToToml(const FDateTime& dateTime, toml::v2::date& date, toml::v2::time& time)
{
	int month, day, year;
	FDateTime::GetDate(dateTime, day, month, year);
	date.day = day;
	date.month = month;
	date.year = year;

	time.hour = FDateTime::GetHour(dateTime);
	time.minute = FDateTime::GetMinute(dateTime);
	time.second = FDateTime::GetSecond(dateTime);
	time.nanosecond = FDateTime::GetNanosecond(dateTime);
}

FDateTime TomlToDateTime(toml::v2::date& date, toml::v2::time& time)
{
	return FDateTime(date.year, date.month, date.day,
		time.hour, time.minute, time.second, time.nanosecond * 1000000, time.nanosecond * 1000);
}

template<typename T>
std::vector<T> TomlToVector(const toml::v2::array& array)
{
	std::vector<T> vector;
	vector.reserve(array.size());
	for (auto&& elem : array)
	{
		T el = (T)(*elem.as<T>());
		vector.push_back(el);
	}
	return vector;
}

template<typename T>
std::vector<T> TomlToVector(const toml::v2::impl::wrap_node<toml::v2::array>* array)
{
	const toml::v2::array* realArray = array->as_array();
	return TomlToVector<T>(*realArray);
}

template<typename T>
toml::array VectorToToml(const std::vector<T> vector)
{
	toml::array arr;
	arr.reserve(vector.size());

	for (size_t i = 0; i < vector.size(); i++)
	{
		arr.push_back(vector[i]);
	}

	return arr;
}