#pragma once
#include <string>

struct FColor
{
	float r;
	float g;
	float b;
	float a;

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
	std::string CMYKString() const;

	float C() const;
	float M() const;
	float Y() const;
	float K() const;

	static FColor Lerp(FColor start, FColor end, float t);
	static FColor RandomColor(bool randomAlpha=true);

	// Colors
	static const FColor Black;
	static const FColor Charcoal;
	static const FColor Gunmetal;
	static const FColor Midnight;
	static const FColor Night;
	static const FColor Red;
	static const FColor White;
};