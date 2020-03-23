#pragma once
#include <string>
using namespace std;

enum EDayOfWeek
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

enum EMonthOfYear
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

	long long ticks;

	const FDateTime operator+(const FDateTime& other);
	FDateTime operator+=(const FDateTime& other);
	const FDateTime operator-(const FDateTime& other);
	FDateTime operator-=(const FDateTime& other);
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
	static int GetMonth(const FDateTime& dateTime);
	static EMonthOfYear GetMonthOfYear(const FDateTime& dateTime);
	static int GetYear(const FDateTime& dateTime);
	static void GetDate(const FDateTime& dateTime, int& day, int& month, int& year);

	static FDateTime Now();
	static FDateTime NowHighRes();

	static string ToString(const FDateTime& dateTime);
	static string ToString(const FDateTime& dateTime, const string format);
	static string DateToString(const FDateTime& dateTime);
	static string SecondsToString(const FDateTime& dateTime);
	static string TimeToString(const FDateTime& dateTime);
};

