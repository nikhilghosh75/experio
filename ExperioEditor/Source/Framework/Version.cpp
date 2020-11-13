#include "Version.h"
#include <sstream>
#include "Runtime/Containers/LString.h"

FVersion::FVersion()
{
	this->major = 0;
	this->minor = 0;
	this->patch = 0;
	this->type = EVersionType::Alpha;
}

FVersion::FVersion(uint8_t major)
{
	this->major = major;
	this->minor = 0;
	this->patch = 0;
	this->type = EVersionType::Final;
}

FVersion::FVersion(uint8_t major, uint8_t minor)
{
	this->major = major;
	this->minor = minor;
	this->patch = 0;
	this->type = EVersionType::Final;
}

FVersion::FVersion(uint8_t major, uint8_t minor, uint8_t patch)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->type = EVersionType::Final;
}

FVersion::FVersion(uint8_t major, uint8_t minor, uint8_t patch, EVersionType versionType)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->type = versionType;
}

bool FVersion::operator==(const FVersion & v) const
{
	return this->major == v.major && this->minor == v.minor && this->patch == v.patch && this->type == v.type;
}

bool FVersion::operator!=(const FVersion & v) const
{
	return this->major != v.major || this->minor != v.minor || this->patch != v.patch || this->type != v.type;
}

bool FVersion::operator<(const FVersion & v) const
{
	if (this->major != v.major)
		return this->major < v.major;
	if (this->minor != v.minor)
		return this->minor < v.minor;
	if (this->patch != v.patch)
		return this->patch < v.patch;
	
	if (v.type == EVersionType::Final && this->type != EVersionType::Final)
		return true;
	if (v.type != EVersionType::Final && this->type == EVersionType::Final)
		return false;
	if (v.type == EVersionType::Beta && this->type != EVersionType::Beta)
		return true;
	return false;
}

bool FVersion::operator>(const FVersion & v) const
{
	if (this->major != v.major)
		return this->major > v.major;
	if (this->minor != v.minor)
		return this->minor > v.minor;
	if (this->patch != v.patch)
		return this->patch > v.patch;

	if (this->type == EVersionType::Final && v.type != EVersionType::Final)
		return true;
	if (this->type != EVersionType::Final && v.type == EVersionType::Final)
		return false;
	if (this->type == EVersionType::Beta && v.type != EVersionType::Beta)
		return true;
	return false;
}

bool FVersion::operator<=(const FVersion & v) const
{
	if (this->major != v.major)
		return this->major < v.major;
	if (this->minor != v.minor)
		return this->minor < v.minor;
	if (this->patch != v.patch)
		return this->patch < v.patch;

	if (v.type == EVersionType::Final && this->type != EVersionType::Final)
		return true;
	if (v.type != EVersionType::Final && this->type == EVersionType::Final)
		return false;
	if (v.type == EVersionType::Beta && this->type != EVersionType::Beta)
		return true;
	if (v.type != EVersionType::Beta && this->type == EVersionType::Beta)
		return false;
	return true;
}

bool FVersion::operator>=(const FVersion & v) const
{
	if (this->major != v.major)
		return this->major > v.major;
	if (this->minor != v.minor)
		return this->minor > v.minor;
	if (this->patch != v.patch)
		return this->patch > v.patch;

	if (this->type == EVersionType::Final && v.type != EVersionType::Final)
		return true;
	if (this->type != EVersionType::Final && v.type == EVersionType::Final)
		return false;
	if (this->type == EVersionType::Beta && v.type != EVersionType::Beta)
		return true;
	if (this->type != EVersionType::Beta && v.type == EVersionType::Beta)
		return true;
	return false;
}

std::string FVersion::ToString() const
{
	std::stringstream ss;
	ss << this->major << "." << this->minor << "." << this->patch;
	switch (this->type)
	{
	case EVersionType::Alpha:
		ss << "a"; break;
	case EVersionType::Beta:
		ss << "b"; break;
	case EVersionType::Final:
		ss << "f"; break;
	}
	return ss.str();
}

FVersion::FVersion(const std::string & str)
{
	std::vector<size_t> v = LString::FindAllOfChar(str, '.');
	this->major = LString::StringToUInt(str.substr(0, v[0]));
	this->minor = LString::StringToUInt(str.substr(v[0] + 1, v[1] - v[0] - 1));
	this->patch = LString::StringToUInt(str.substr(v[1] + 1));
	
	switch (v[v.size() - 1])
	{
	case 'a':
	case 'A':
		this->type = EVersionType::Alpha; break;
	case 'b':
	case 'B':
		this->type = EVersionType::Beta; break;
	default:
		this->type = EVersionType::Final;
	}
}

bool FVersion::IsValid(const std::string & str)
{
	std::vector<size_t> v = LString::FindAllOfChar(str, '.');
	if (v.size() != 2) 
		return false;

	for (int i = 0; i < str.size() - 1; i++)
	{
		if (!LString::IsNumeric(str[i]) && str[i] != '.') 
			return false;
	}

	return true;
}

FVersion & FVersion::operator++()
{
	this->patch++;
	return *this;
}

FVersion & FVersion::NextPatch() const
{
	return FVersion(this->major, this->minor, this->patch + 1, EVersionType::Final);
}

FVersion & FVersion::NextMinor() const
{
	return FVersion(this->major, this->minor + 1, 0, EVersionType::Final);
}

FVersion & FVersion::NextMajor() const
{
	return FVersion(this->major + 1, 0, 0, EVersionType::Final);
}

bool FVersion::IsInRange(const FVersionRange & range) const
{
	return (*this <= range.max) && (*this >= range.min);
}

FVersionRange::FVersionRange()
{
	this->min = FVersion();
	this->max = FVersion();
}

FVersionRange::FVersionRange(FVersion min, FVersion max)
{
	this->min = min;
	this->max = max;
}
