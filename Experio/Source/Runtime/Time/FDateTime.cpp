#include "FDateTime.h"
#include <iostream>
#include <string>
#include <sstream>
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
const int NANOSECONDSPERTICKS = 100;

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

int FDateTime::GetNanosecond(const FDateTime & dateTime)
{
	return (dateTime.ticks * NANOSECONDSPERTICKS) % 1000000000;
}

int FDateTime::GetMicrosecond(const FDateTime & dateTime)
{
	return (dateTime.ticks / TICKSPERMICROSECOND) % 1000;
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

int FDateTime::GetNanosecond() const
{
	return GetNanosecond(*this);
}

int FDateTime::GetMillisecond() const
{
	return GetMillisecond(*this);
}

int FDateTime::GetSecond() const
{
	return GetSecond(*this);
}

int FDateTime::GetMinute() const
{
	return GetMinute(*this);
}

int FDateTime::GetHour() const
{
	return GetHour(*this);
}

int FDateTime::GetHourAM() const
{
	return GetHourAM(*this);
}

int FDateTime::GetDay() const
{
	return GetDay(*this);
}

EDayOfWeek FDateTime::GetDayOfWeek() const
{
	return GetDayOfWeek(*this);
}

int FDateTime::GetMonth() const
{
	return GetMonth(*this);
}

EMonthOfYear FDateTime::GetMonthOfYear() const
{
	return GetMonthOfYear(*this);
}

int FDateTime::GetYear() const
{
	return GetYear(*this);
}

void FDateTime::GetDate(int & day, int & month, int & year) const
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

	return s;
}

std::string FDateTime::ToString(const FDateTime & dateTime, const std::string format)
{
	std::stringstream ss;
	
	for (size_t i = 0; i < format.size(); i++)
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{
			case 'a': // am/pm
				if (GetHour(dateTime) > 12)
					ss << "pm";
				else
					ss << "am";
				break;
			case 'A': // AM/PM
				if (GetHour(dateTime) > 12)
					ss << "PM";
				else
					ss << "AM";
				break;
			case 'd': // Day (2 digit) 
			{
				int day = GetDay(dateTime);
				if (GetDay(dateTime) >= 10)
					ss << day;
				else
					ss << "0" << day;
				break;
			}
			case 'D': // Day (1 or 2 Digits)
				ss << GetDay(dateTime);
				break;
			case 'e':
				if (dateTime.ticks > 0)
					ss << "AD";
				else
					ss << "BC";
				break;
			case 'h':
			{
				int hour = GetHour(dateTime);
				if (hour >= 10)
					ss << hour;
				else
					ss << "0" << hour;
				break;
			}
			case 'H':
				ss << GetHour(dateTime);
				break;
			case 'm':
				ss << GetMillisecond(dateTime);
				break;
			case 'M':
				if (i + 2 < format.size() && format[i + 2] == 'M')
				{
					ss << MonthToThreeChar(GetMonth(dateTime));
					i++;
				}
				else
					ss << GetMonth(dateTime);
				break;
			case 's':
			{
				int seconds = GetSecond(dateTime);
				if (seconds >= 10)
					ss << seconds;
				else
					ss << "0" << seconds;
			}
				break;
			case 'u':
			{
				int microseconds = GetMicrosecond(dateTime);
				if (microseconds >= 100)
					ss << microseconds;
				else if (microseconds >= 10)
					ss << "0" << microseconds;
				else
					ss << "00" << microseconds;
			}
				break;
			case 'X':
				ss << dateTime.ticks;
				break;
			case 'y':
			{
				int year = GetYear(dateTime);
				if (i + 2 < format.size() && format[i + 2] == 'y') // yy
				{
					int twoDigitYear = year % 100;
					ss << twoDigitYear;
					i += 2;
				}
				else
				{
					ss << year;
				}
			}
				break;
			}
			i++;
		}
		else
		{
			ss << format[i];
		}
	}
	return ss.str();
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

std::string FDateTime::MonthToThreeChar(int month)
{
	switch (month)
	{
	case 1: return "Jan";
	case 2: return "Feb";
	case 3: return "Mar";
	case 4: return "Apr";
	case 5: return "May";
	case 6: return "Jun";
	case 7: return "Jul";
	case 8: return "Aug";
	case 9: return "Sep";
	case 10: return "Oct";
	case 11: return "Nov";
	case 12: return "Dec";
	}
	return "   ";
}

FDateTime FDateTime::TimeSinceUnixEpoch(const FDateTime & dateTime)
{
	return FDateTime(dateTime.ticks - TICKSSINCEUNIXEPOCH);
}

FDuration operator-(const FDateTime & date1, const FDateTime & date2)
{
	return FDuration(date1.ticks - date2.ticks);
}
