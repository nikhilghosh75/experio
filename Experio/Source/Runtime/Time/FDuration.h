#pragma once
#include <string>

struct FDuration
{
	FDuration();
	FDuration(long long ticks);
	FDuration(int milliseconds, int seconds, int hours = 0, int days = 0, int years = 0);

	long long ticks;

	FDuration operator+(const FDuration& other);
	FDuration operator+=(const FDuration& other);
	FDuration operator-(const FDuration& other);
	FDuration operator-=(const FDuration& other);

	bool operator==(const FDuration& other);
	bool operator!=(const FDuration& other);
	bool operator>(const FDuration& other);
	bool operator<(const FDuration& other);
	bool operator>=(const FDuration& other);
	bool operator<=(const FDuration& other);

	int GetMillisecond() const;
	int GetSecond() const;
	int GetMinute() const;
	int GetHour() const;
	int GetDay() const;
	int GetYear() const;

	static int GetMillisecond(const FDuration& duration);
	static int GetSecond(const FDuration& duration);
	static int GetMinute(const FDuration& duration);
	static int GetHour(const FDuration& duration);
	static int GetDay(const FDuration& duration);
	static int GetYear(const FDuration& duration);

	static const FDuration microsecond;
	static const FDuration millisecond;
	static const FDuration second;
	static const FDuration minute;
	static const FDuration hour;
	static const FDuration year;

	static std::string ToString(const FDuration& duration);
	static std::string ToString(const FDuration& duration, const std::string& format);
};