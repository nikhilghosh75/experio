#pragma once
#include <stdint.h>
#include <string>

struct FVersionRange;

enum class EVersionType : uint8_t
{
	Alpha,
	Beta,
	Final
};

struct FVersion
{
	uint8_t major;
	uint8_t minor;
	uint8_t patch;
	EVersionType type;

	// Constructors
	FVersion();
	FVersion(uint8_t major);
	FVersion(uint8_t major, uint8_t minor);
	FVersion(uint8_t major, uint8_t minor, uint8_t patch);
	FVersion(uint8_t major, uint8_t minor, uint8_t patch, EVersionType versionType);

	// Operators (==, !=, <, >, <=, >=)
	bool operator==(const FVersion& v) const;
	bool operator!=(const FVersion& v) const;
	bool operator<(const FVersion& v) const;
	bool operator>(const FVersion& v) const;
	bool operator<=(const FVersion& v) const;
	bool operator>=(const FVersion& v) const;

	// From/To String
	operator std::string() const { return ToString();};
	std::string ToString() const;
	FVersion(const std::string& str);
	static bool IsValid(const std::string& str);

	// Increment
	FVersion& operator++();

	FVersion& NextPatch() const;
	FVersion& NextMinor() const;
	FVersion& NextMajor() const;

	// IsInRange
	bool IsInRange(const FVersionRange& range) const;
};

struct FVersionRange
{
	FVersion min;
	FVersion max;

	FVersionRange();
	FVersionRange(FVersion min, FVersion max);
};