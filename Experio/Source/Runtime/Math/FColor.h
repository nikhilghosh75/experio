#pragma once
#include <string>
#include "FVector3.h"
#include "FVector4.h"
#include "imgui.h"

struct FColor
{
	float r; // stored between 0 and 1
	float g; // stored between 0 and 1
	float b; // stored between 0 and 1
	float a; // stored between 0 and 1

	FColor();
	FColor(float r, float g, float b);
	FColor(float r, float g, float b, float a);
	FColor(int r, int g, int b, int a);
	FColor(std::string s);

	static FColor FromHex(std::string s);
	static FColor FromString(std::string s);
	static FColor FromCMYK(float c, float m, float y, float k);
	static FColor FromCMYK(std::string s);
	static FColor FromRGBString(std::string s);

	std::string Hex() const;
	std::string RGBAString() const;
	std::string RGBAStringInt() const;
	std::string CMYKString() const;

	float C() const;
	float M() const;
	float Y() const;
	float K() const;

	static FColor Lerp(FColor start, FColor end, float t);
	static FColor RandomColor(bool randomAlpha=true);

	operator FVector3() const;
	operator FVector4() const;
	operator ImVec4() const { return ImVec4(this->r, this->g, this->b, this->a); }

	explicit operator uint32_t() const;
};