#include "FColor.h"
#include "LMath.h"
#include "../Containers/LString.h"
#include <sstream>
#include <iomanip>

FColor::FColor()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

FColor::FColor(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1.f;
}

FColor::FColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

FColor::FColor(int r, int g, int b, int a)
{
	this->r = (float)r / 255;
	this->g = (float)g / 255;
	this->b = (float)b / 255;
	this->a = (float)a / 255;
}

FColor::FColor(std::string s)
{
	*this = FColor::FromString(s);
}

FColor FColor::FromHex(std::string s)
{
	FColor returnColor = FColor(
		LString::HexStringToInt(s.substr(1, 2)),
		LString::HexStringToInt(s.substr(3, 2)),
		LString::HexStringToInt(s.substr(5, 2))
	);

	return returnColor;
}

FColor FColor::FromString(std::string s)
{
	char firstChar = s[0];

	switch (firstChar)
	{
	case 'R':
	case 'r':
		return FromRGBString(s);
	case 'C':
	case 'c':
		return FromCMYK(s);
	case '#':
		return FromHex(s);
	}

	return FColor();
}

FColor FColor::FromCMYK(float c, float m, float y, float k)
{
	return FColor((1 - c) * (1 - k), (1 - m) * (1 - k), (1 - y) * (1 - k));
}

FColor FColor::FromCMYK(std::string s)
{
	float data[4];
	data[3] = 0;

	int i = s.find('(');

	for (int j = 0; j < 4; j++)
	{
		int start = i;
		while (s[i] != ',' || s[i] != ')')
		{
			i++;
		}

		data[i] = atof(s.substr(start, i - start).c_str());
	}

	return FColor::FromCMYK(data[0], data[1], data[2], data[3]);
}

FColor FColor::FromRGBString(std::string s)
{
	float data[4];
	data[3] = 0;

	int i = s.find('(');

	for (int j = 0; j < 4; j++)
	{
		int start = i;
		while (s[i] != ',' || s[i] != ')')
		{
			i++;
		}

		data[i] = atof(s.substr(start, i - start).c_str());
	}

	return FColor(data[0], data[1], data[2], data[3]);
}

std::string FColor::Hex() const
{
	std::stringstream ss;
	ss << "#" << std::hex << (int)(this->r * 255)
		<< std::hex << (int)(this->g * 255)
		<< std::hex << (int)(this->b * 255)
		<< std::hex << (int)(this->a * 255);
	return ss.str();
}

std::string FColor::RGBAString() const
{
	std::stringstream ss;
	ss << "rgb(" << this->r << ", " << this->g << ", " << this->b << ", " << this->a << ")";
	return ss.str();
}

std::string FColor::RGBAStringInt() const
{
	std::stringstream ss;
	ss << "rgb(" << (int)(this->r * 255) << ", " << (int)(this->g * 255)
		<< ", " << (int)(this->b * 255) << ", " << (int)(this->a * 255) << ")";
	return ss.str();
}

std::string FColor::CMYKString() const
{
	float c = C();
	float m = M();
	float y = Y();
	float k = K();

	std::stringstream ss;
	ss << "cmyk(" << c << ", " << m << ", " << y << ", " << k << ")";
	return ss.str();
}

float FColor::C() const
{
	float k = K();
	return (1 - this->r - k) / (1 - k);
}

float FColor::M() const
{
	float k = K();
	return (1 - this->g - k) / (1 - k);
}

float FColor::Y() const
{
	float k = K();
	return (1 - this->b - k) / (1 - k);
}

float FColor::K() const
{
	float max = this->r > this->g ? this->r : this->g;
	max = this->b > max ? this->b : max;
	return 1 - max;
}

FColor FColor::Lerp(FColor start, FColor end, float t)
{
	return FColor(
		LMath::Lerp(start.r, end.r, t),
		LMath::Lerp(start.g, end.g, t),
		LMath::Lerp(start.b, end.b, t),
		LMath::Lerp(start.a, start.b, t)
	);
}

FColor FColor::RandomColor(bool randomAlpha)
{
	return FColor(
		(rand() % 256) / 256.f,
		(rand() % 256) / 256.f,
		(rand() % 256) / 256.f,
		randomAlpha ? (rand() % 256) / 256.f : 1.f
	);
}

FColor::operator FVector3() const
{
	return FVector3(this->r, this->g, this->b);
}

FColor::operator FVector4() const
{
	return FVector4(this->r, this->g, this->b, this->a);
}

FColor::operator uint32_t() const
{
	return ((uint32_t)(this->r * 255.00f)) | 
		((uint32_t)(this->g * 255.00f) << 8)  |
		((uint32_t)(this->b * 255.00f) << 16) |
		((uint32_t)(this->a * 255.00f) << 24);
}
