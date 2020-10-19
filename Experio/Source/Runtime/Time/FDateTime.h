#pragma once
#include <string>
#include "FDuration.h"

enum class EDayOfWeek
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

enum class EMonthOfYear
{
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

// A tick is 0.1 microseconds (= 100 nanoseconds)
// Starts at Midnight 00:00:00, January 1, 0001.

struct FDateTime
{
public:
	FDateTime();
	FDateTime(long long inTicks);
	FDateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);

	static FDateTime FromUnixEpoch(long long ticksSinceEpoch);
	static FDateTime From1601Epoch(long long ticksSinceEpoch);

	long long ticks;

	const FDateTime operator+(const FDuration& duration);
	FDateTime operator+=(const FDuration& other);
	const FDateTime operator-(const FDuration& other);
	FDateTime operator-=(const FDuration& other);
	const bool operator==(const FDateTime& other);
	const bool operator!=(const FDateTime& other);
	const bool operator>(const FDateTime& other);
	const bool operator<(const FDateTime& other);
	const bool operator>=(const FDateTime& other);
	const bool operator<=(const FDateTime& other);

	static bool IsValidDateTime(const FDateTime& dateTime);
	static bool IsValidDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond);

	static bool IsLeapYear(const FDateTime& dateTime);
	static bool IsLeapYear(int year);

	static int GetMillisecond(const FDateTime& dateTime);
	static int GetSecond(const FDateTime& dateTime);
	static int GetMinute(const FDateTime& dateTime);
	static int GetHour(const FDateTime& dateTime);
	static int GetHourAM(const FDateTime& dateTime);
	static int GetDay(const FDateTime& dateTime);
	static EDayOfWeek GetDayOfWeek(const FDateTime& dateTime);
	static int GetMonth(const FDateTime& dateTime); // Indexed at 1
	static EMonthOfYear GetMonthOfYear(const FDateTime& dateTime);
	static int GetYear(const FDateTime& dateTime);
	static void GetDate(const FDateTime& dateTime, int& day, int& month, int& year);

	int GetMillisecond();
	int GetSecond();
	int GetMinute();
	int GetHour();
	int GetHourAM();
	int GetDay();
	EDayOfWeek GetDayOfWeek();
	int GetMonth();
	EMonthOfYear GetMonthOfYear();
	int GetYear();
	void GetDate(int& day, int& month, int& year);

	static FDateTime Now();
	static FDateTime NowHighRes();

	static std::string ToString(const FDateTime& dateTime);
	static std::string ToString(const FDateTime& dateTime, const std::string format);
	static std::string DateToString(const FDateTime& dateTime);
	static std::string SecondsToString(const FDateTime& dateTime);
	static std::string TimeToString(const FDateTime& dateTime);

	static std::string MonthToThreeChar(int month); // Indexed at 1

	static FDateTime TimeSinceUnixEpoch(const FDateTime& dateTime);
};

FDuration operator-(const FDateTime& date1, const FDateTime& date2);