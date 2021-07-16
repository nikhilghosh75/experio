#pragma once
#include <stdint.h>
#include <string>

struct FPolynomialPoint
{
	float coefficient;
	unsigned int power;
};

class Polynomial
{
	FPolynomialPoint* points;
	uint32_t numPoints;
	uint32_t capacity;

public:
	Polynomial();
	Polynomial(uint32_t capacity);
	Polynomial(FPolynomialPoint* points, uint32_t numPoints);
	Polynomial(FPolynomialPoint* points, uint32_t numPoints, uint32_t capacity);
	Polynomial(const std::string& str);

	std::string ToString() const;

	float Get(float x) const;
};