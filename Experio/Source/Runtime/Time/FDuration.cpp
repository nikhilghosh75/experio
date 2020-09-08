#include "FDuration.h"
#include <iostream>
#include <sstream>

const long long MAXTICKS = 8640000000000000;
const long long TICKSPERYEAR = 315569520000000;
const long long TICKSPERDAY = 864000000000;
const long long TICKSPERHOUR = 36000000000;
const long long TICKSPERMINUTE = 600000000;
const int TICKSPERSECOND = 10000000;
const int TICKSPERMILLISECOND = 10000;
const int TICKSPERMICROSECOND = 10;
const long long TICKSSINCE1601 = 504912960000000000;
const long long TICKSINCEUNIXEPOCH = 621672192000000000;

FDuration::FDuration()
{
	this->ticks = 0;
}

FDuration::FDuration(long long ticks)
{
	this->ticks = ticks;
}

FDuration::FDuration(int milliseconds, int seconds, int hours, int days, int years)
{
	this->ticks =
		milliseconds * TICKSPERMILLISECOND +
		seconds * TICKSPERSECOND +
		hours * TICKSPERHOUR +
		days * TICKSPERDAY +
		years * TICKSPERYEAR;
}

FDuration FDuration::operator+(const FDuration & other)
{
	return FDuration(this->ticks + other.ticks);
}

FDuration FDuration::operator+=(const FDuration & other)
{
	this->ticks += other.ticks;
	return FDuration(this->ticks + other.ticks);
}

FDuration FDuration::operator-(const FDuration & other)
{
	return FDuration(this->ticks - other.ticks);
}

FDuration FDuration::operator-=(const FDuration & other)
{
	this->ticks -= other.ticks;
	return FDuration(this->ticks - other.ticks);
}

int FDuration::GetMillisecond(const FDuration & duration)
{
	return duration.ticks / TICKSPERMILLISECOND;
}

int FDuration::GetSecond(const FDuration & duration)
{
	return duration.ticks / TICKSPERSECOND;
}

int FDuration::GetMinute(const FDuration & duration)
{
	return duration.ticks / TICKSPERMINUTE;
}

int FDuration::GetHour(const FDuration & duration)
{
	return duration.ticks / TICKSPERHOUR;
}

int FDuration::GetDay(const FDuration & duration)
{
	return duration.ticks / TICKSPERDAY;
}

int FDuration::GetYear(const FDuration & duration)
{
	return duration.ticks / TICKSPERYEAR;
}

std::string FDuration::ToString(const FDuration & duration)
{
	std::stringstream ss;
	if (duration.ticks > TICKSPERYEAR)
	{
		ss << GetYear(duration) << " y ";
	}
	ss << GetDay(duration) << " d ";
	ss << GetHour(duration) << " h ";
	ss << GetMinute(duration) << " m";
	ss << GetSecond(duration) << " s";
	ss << GetSecond(duration) << " ms";
	return ss.str();
}

std::string FDuration::ToString(const FDuration & duration, const std::string & format)
{
	return std::string();
}