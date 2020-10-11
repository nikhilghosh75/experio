#include "FDateTime.h"
#include <iostream>
#include <string>
#include "windows.h"
#include "../Containers/LString.h"

const int DAYSTOMONTH[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const int DAYSINYEAR = 365;
const int DAYSINCYCLE = 146097; // 1 cycle is 400 years
const long long MAXTICKS = 8640000000000000;
const long long TICKSPERDAY = 864000000000;
const long long TICKSPERHOUR = 36000000000;
const long long TICKSPERMINUTE = 600000000;
const int TICKSPERSECOND = 10000000;
const int TICKSPERMILLISECOND = 10000;
const int TICKSPERMICROSECOND = 10;
const long long TICKSSINCE1601 = 504912960000000000;
const long long TICKSSINCEUNIXEPOCH = 621672192000000000;

void DateTimeTest()
{
	FDateTime testDate(2018, 4, 22, 13, 2);
	std::cout << "Ticks: " << testDate.ticks << std::endl;
	int month, day, year;
	FDateTime::GetDate(testDate, day, month, year);
	std::cout << month << std::endl;
	std::cout << day << std::endl;
	std::cout << year << std::endl;
	FDateTime now = FDateTime::Now();
	FDateTime nowHighRes = FDateTime::NowHighRes();
	std::cout << FDateTime::GetMinute(nowHighRes) << std::endl;
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

	long long totalSeconds = hour * 3600 + minute * 60 + second;

	ticks = totalDays * TICKSPERDAY + totalSeconds * TICKSPERSECOND 
		+ millisecond * TICKSPERMILLISECOND 
		+ microsecond * TICKSPERMICROSECOND;
}

FDateTime FDateTime::FromUnixEpoch(long long ticksSinceEpoch)
{
	return FDateTime(ticksSinceEpoch + TICKSSINCEUNIXEPOCH);
}

FDateTime FDateTime::From1601Epoch(long long ticksSinceEpoch)
{
	return FDateTime(ticksSinceEpoch + TICKSSINCE1601);
}

const FDateTime FDateTime::operator+(const FDuration & duration)
{
	return FDateTime(this->ticks + duration.ticks);
}

FDateTime FDateTime::operator+=(const FDuration & duration)
{
	this->ticks += duration.ticks;
	return FDateTime(this->ticks + duration.ticks);
}

const FDateTime FDateTime::operator-(const FDuration & duration)
{
	return FDateTime(this->ticks - duration.ticks);
}

FDateTime FDateTime::operator-=(const FDuration & duration)
{
	this->ticks -= duration.ticks;
	return FDateTime(this->ticks - duration.ticks);
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

int FDateTime::GetMillisecond(const FDateTime & dateTime)
{
	return (dateTime.ticks/TICKSPERMILLISECOND) % 1000;
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
			month = i;
			day = daysInCurrentYear - DAYSTOMONTH[i - 1] + 1;
			return;
		}
	}
}

int FDateTime::GetMillisecond()
{
	return GetMillisecond(*this);
}

int FDateTime::GetSecond()
{
	return GetSecond(*this);
}

int FDateTime::GetMinute()
{
	return GetMinute(*this);
}

int FDateTime::GetHour()
{
	return GetHour(*this);
}

int FDateTime::GetHourAM()
{
	return GetHourAM(*this);
}

int FDateTime::GetDay()
{
	return GetDay(*this);
}

EDayOfWeek FDateTime::GetDayOfWeek()
{
	return GetDayOfWeek(*this);
}

int FDateTime::GetMonth()
{
	return GetMonth(*this);
}

EMonthOfYear FDateTime::GetMonthOfYear()
{
	return GetMonthOfYear(*this);
}

int FDateTime::GetYear()
{
	return GetYear(*this);
}

void FDateTime::GetDate(int & day, int & month, int & year)
{
	return GetDate(*this, day, month, year);
}

FDateTime FDateTime::Now()
{
#ifdef PLATFORM_WINDOWS
	SYSTEMTIME st;
	GetSystemTime(&st);
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

std::string FDateTime::ToString(const FDateTime & dateTime)
{
	int month, day, year;
	GetDate(dateTime, day, month, year);
	std::string s = std::to_string(month);
	s += "/" + std::to_string(day);
	s += "/" + std::to_string(year);

	if (year < 0)
	{
		s += " BC";
	}

	s += " " + std::to_string(GetHour(dateTime));
	s += ":" + std::to_string(GetMinute(dateTime));
	s += ":" + std::to_string(GetSecond(dateTime));
	s += ":" + std::to_string(GetMillisecond(dateTime));

	return std::string();
}

std::string FDateTime::ToString(const FDateTime & dateTime, const std::string format)
{
	std::string s;
	s.resize(format.length());
	int n = format.length();
	for (int i = 0; i < n; i++)
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{
			case 'a': // am/pm
				if (GetHour(dateTime) > 12)
				{
					s[i] = 'p';
					s[i + 1] = 'm';
				}
				else
				{
					s[i] = 'a';
					s[i + 1] = 'm';
				}
				break;
			case 'A': // AM/PM
				if (GetHour(dateTime) > 12)
				{
					s[i] = 'P';
					s[i + 1] = 'M';
				}
				else
				{
					s[i] = 'A';
					s[i + 1] = 'M';
				}
				break;
			case 'd':
				if (GetDay(dateTime) >= 10)
				{
					s[i] = LString::DigitToChar(GetDay(dateTime) / 10);
					s[i + 1] = LString::DigitToChar(GetDay(dateTime) % 10);
				}
				else
				{
					s[i] = 0;
					s[i + 1] = LString::DigitToChar(GetDay(dateTime));
				}
				break;
			case 'D':
				// TO-DO
				break;
			case 'e':
				if (dateTime.ticks > 0)
				{
					s[i] = 'A';
					s[i + 1] = 'D';
				}
				else
				{
					s[i] = 'B';
					s[i + 1] = 'C';
				}
				break;
			case 'h':
				if (FDateTime::GetHour(dateTime) < 10)
				{
					s[i] = '0';
					s[i + 1] = LString::DigitToChar(GetHour(dateTime));
				}
				else
				{
					s[i] = LString::DigitToChar(GetHour(dateTime) / 10);
					s[i + 1] = LString::DigitToChar(GetHour(dateTime) % 10);
				}
			}
			i++;
		}
	}
	return s;
}

std::string FDateTime::DateToString(const FDateTime & dateTime)
{
	int month, day, year;
	GetDate(dateTime, day, month, year);
	std::string s = std::to_string(month);
	s += "/" + std::to_string(day);
	s += "/" + std::to_string(year);

	if (year < 0)
	{
		s += " BC";
	}
	return s;
}

std::string FDateTime::SecondsToString(const FDateTime & dateTime)
{
	return std::to_string((dateTime.ticks / (float)TICKSPERSECOND));
}

std::string FDateTime::TimeToString(const FDateTime & dateTime)
{
	std::string s = std::to_string(GetHour(dateTime));
	s += ":" + std::to_string(GetMinute(dateTime));
	s += ":" + std::to_string(GetSecond(dateTime));
	s += ":" + std::to_string(GetMillisecond(dateTime));
	return s;
}

FDateTime FDateTime::TimeSinceUnixEpoch(const FDateTime & dateTime)
{
	return FDateTime(dateTime.ticks - TICKSSINCEUNIXEPOCH);
}

FDuration operator-(const FDateTime & date1, const FDateTime & date2)
{
	return FDuration(date1.ticks - date2.ticks);
}
