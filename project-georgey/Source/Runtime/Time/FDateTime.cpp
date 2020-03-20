#include "FDateTime.h"
#include <iostream>
#include <string>
#include "windows.h"
using namespace std;

const int DAYSTOMONTH[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const int DAYSINYEAR = 365;
const int DAYSINCYCLE = 146097;
const long long MAXTICKS = 8640000000000000;
const long long TICKSPERDAY = 864000000000;
const long long TICKSPERHOUR = 36000000000;
const long long TICKSPERMINUTE = 600000000;
const int TICKSPERSECOND = 10000000;
const int TICKSPERMILLISECOND = 10000;
const int TICKSPERMICROSECOND = 10;
const long long TICKSSINCE1601 = 504912960000000000;


void DateTimeTest()
{
	FDateTime testDate(2018, 4, 22, 13, 2);
	cout << "Ticks: " << testDate.ticks << endl;
	int month, day, year;
	FDateTime::GetDate(testDate, day, month, year);
	cout << month << endl;
	cout << day << endl;
	cout << year << endl;
	FDateTime now = FDateTime::Now();
	FDateTime nowHighRes = FDateTime::NowHighRes();
	cout << FDateTime::GetMinute(nowHighRes) << endl;
}

FDateTime::FDateTime()
{
	ticks = 0;
}

FDateTime::FDateTime(long long inTicks)
{
	ticks = inTicks;
}

FDateTime::FDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
{
	long long totalDays = 0;

	if (IsLeapYear(year) && month > 2)
	{
		totalDays++;
	}

	year--;

	totalDays += (long)year * DAYSINYEAR;
	totalDays += (long)(year / 4) - (long)(year / 100) + (long)(year / 400); // Leap Year
	totalDays += (long)DAYSTOMONTH[month - 1];
	totalDays += day - 1;
	totalDays += 2; // Adjusting for something

	cout << "TOTAL DAYS: " << totalDays << endl;
	long long totalSeconds = hour * 3600 + minute * 60 + second;

	ticks = totalDays * TICKSPERDAY + totalSeconds * TICKSPERSECOND 
		+ millisecond * TICKSPERMILLISECOND 
		+ microsecond * TICKSPERMICROSECOND;
}

const FDateTime FDateTime::operator+(const FDateTime & other)
{
	return FDateTime(this->ticks + other.ticks);
}

FDateTime FDateTime::operator+=(const FDateTime & other)
{
	return *this + other;
}

const FDateTime FDateTime::operator-(const FDateTime & other)
{
	return FDateTime(this->ticks - other.ticks);
}

FDateTime FDateTime::operator-=(const FDateTime & other)
{
	return *this - other;
}

const bool FDateTime::operator==(const FDateTime & other)
{
	if (this->ticks == other.ticks)
	{
		return true;
	}
	return false;
}

const bool FDateTime::operator!=(const FDateTime & other)
{
	if (this->ticks != other.ticks)
	{
		return true;
	}
	return false;
}

const bool FDateTime::operator>(const FDateTime & other)
{
	if (this->ticks > other.ticks)
	{
		return true;
	}
	return false;
}

const bool FDateTime::operator<(const FDateTime & other)
{
	if (this->ticks < other.ticks)
	{
		return true;
	}
	return false;
}

const bool FDateTime::operator>=(const FDateTime & other)
{
	if (this->ticks >= other.ticks)
	{
		return true;
	}
	return false;
}

const bool FDateTime::operator<=(const FDateTime & other)
{
	if (this->ticks <= other.ticks)
	{
		return true;
	}
	return false;
}

bool FDateTime::IsValidDateTime(const FDateTime & dateTime)
{
	if (dateTime.ticks > 0 && dateTime.ticks < MAXTICKS)
	{
		return true;
	}
	return false;
}

bool FDateTime::IsValidDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
{
	return false;
}

bool FDateTime::IsLeapYear(const FDateTime & dateTime)
{
	int year = GetYear(dateTime);
	if (year % 4 == 0)
	{
		if (year % 400 == 0)
		{
			return true;
		}
		else if (year % 100 == 0)
		{
			return false;
		}
		return true;
	}
	return false;
}

bool FDateTime::IsLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 400 == 0)
		{
			return true;
		}
		else if (year % 100 == 0)
		{
			return false;
		}
		return true;
	}
	return false;
}

int FDateTime::GetSecond(const FDateTime & dateTime)
{
	return (dateTime.ticks/TICKSPERSECOND) % 60;
}

int FDateTime::GetMinute(const FDateTime & dateTime)
{
	return (dateTime.ticks/TICKSPERMINUTE) % 60;
}

int FDateTime::GetHour(const FDateTime & dateTime)
{
	return (dateTime.ticks/TICKSPERHOUR) % 24;
}

int FDateTime::GetHourAM(const FDateTime & dateTime)
{
	int hour = GetHour(dateTime);
	if (hour < 12)
	{
		return hour;
	}
	return hour - 12;
}

int FDateTime::GetDay(const FDateTime & dateTime)
{
	int day, month, year;
	GetDate(dateTime, day, month, year);
	return day;
}

EDayOfWeek FDateTime::GetDayOfWeek(const FDateTime & dateTime)
{
	return static_cast<EDayOfWeek>(dateTime.ticks / TICKSPERDAY);
}

int FDateTime::GetMonth(const FDateTime & dateTime)
{
	int day, month, year;
	GetDate(dateTime, day, month, year);
	return month;
}

EMonthOfYear FDateTime::GetMonthOfYear(const FDateTime & dateTime)
{
	return static_cast<EMonthOfYear>(GetMonth(dateTime));
}

int FDateTime::GetYear(const FDateTime & dateTime)
{
	int daysSinceStart = dateTime.ticks / TICKSPERDAY;
	int daysSinceCycle = daysSinceStart % DAYSINCYCLE; // 1 Cycle is 400 Years
	int leapYears = (daysSinceCycle / (DAYSINYEAR * 4)) - (daysSinceCycle / (DAYSINYEAR * 100));

	int yearInCycle = (daysSinceCycle - leapYears) / 365;
	int year = yearInCycle + 1 + (daysSinceStart / DAYSINCYCLE) * 400;
	return year;
}

void FDateTime::GetDate(const FDateTime & dateTime, int & day, int & month, int & year)
{
	int daysSinceStart = dateTime.ticks / TICKSPERDAY;
	int daysSinceCycle = daysSinceStart % DAYSINCYCLE; // 1 Cycle is 400 Years
	int leapYears = (daysSinceCycle / (DAYSINYEAR * 4)) - (daysSinceCycle / (DAYSINYEAR * 100));
	
	int yearInCycle = (daysSinceCycle - leapYears) / 365;
	year = yearInCycle + 1 + (daysSinceStart / DAYSINCYCLE) * 400;

	int daysInCurrentYear = (daysSinceCycle - leapYears) % 365;
	if (IsLeapYear(year) && daysInCurrentYear > 60)
	{
		daysInCurrentYear--;
	}
	
	for (int i = 1; i < 13; i++)
	{
		if (daysInCurrentYear < DAYSTOMONTH[i])
		{
			month = i - 1;
			day = daysInCurrentYear - DAYSTOMONTH[i - 1] + 1;
			return;
		}
	}
}

FDateTime FDateTime::Now()
{
#ifdef PLATFORM_WINDOWS
	SYSTEMTIME st;
	GetSystemTime(&st);
	cout << st.wMinute << endl;
	return FDateTime(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#endif
}

FDateTime FDateTime::NowHighRes()
{
#ifdef PLATFORM_WINDOWS
	FILETIME ft;
	GetSystemTimePreciseAsFileTime(&ft);
	ULARGE_INTEGER ft_ticks;
	ft_ticks.LowPart = ft.dwLowDateTime;
	ft_ticks.HighPart = ft.dwHighDateTime;
	return FDateTime(ft_ticks.QuadPart + TICKSSINCE1601);
#endif
}

string FDateTime::ToString(const FDateTime & dateTime)
{
	return string();
}

string FDateTime::ToString(const FDateTime & dateTime, const string format)
{
	return string();
}

string FDateTime::DateToString(const FDateTime & dateTime)
{
	return string();
}

string FDateTime::SecondsToString(const FDateTime & dateTime)
{
	return to_string((dateTime.ticks / (float)TICKSPERSECOND));
}

string FDateTime::TimeToString(const FDateTime & dateTime)
{
	return string();
}