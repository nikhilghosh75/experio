#pragma once
#include <string>
#include "FDuration.h"
#include "../../ThirdParty/toml++/toml_date_time.h"

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
	
	// Conversions
	FDateTime(toml::v2::date date, toml::v2::time time);

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

	static int GetNanosecond(const FDateTime& dateTime);
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

	int GetNanosecond() const;
	int GetMillisecond() const;
	int GetSecond() const;
	int GetMinute() const;
	int GetHour() const;
	int GetHourAM() const;
	int GetDay() const;
	EDayOfWeek GetDayOfWeek() const;
	int GetMonth() const;
	EMonthOfYear GetMonthOfYear() const;
	int GetYear() const;
	void GetDate(int& day, int& month, int& year) const;

	static FDateTime Now();
	static FDateTime NowHighRes();

	static std::string ToString(const FDateTime& dateTime);
	static std::string ToString(const FDateTime& dateTime, const std::string format);
	static std::string DateToString(const FDateTime& dateTime);
	static std::string SecondsToString(const FDateTime& dateTime);
	static std::string TimeToString(const FDateTime& dateTime);

	void TimeToToml(toml::v2::date& date, toml::v2::time& time) const;

	static std::string MonthToThreeChar(int month); // Indexed at 1

	static FDateTime TimeSinceUnixEpoch(const FDateTime& dateTime);
};

FDuration operator-(const FDateTime& date1, const FDateTime& date2);