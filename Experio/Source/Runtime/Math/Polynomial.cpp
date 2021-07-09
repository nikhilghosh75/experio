#include "Polynomial.h"
#include "LMath.h"
#include "../Containers/LString.h"

Polynomial::Polynomial()
{
	this->points = nullptr;
	this->capacity = 0;
	this->numPoints = 0;
}

Polynomial::Polynomial(uint32_t capacity)
{
	this->points = new FPolynomialPoint[capacity];
	this->capacity = capacity;
	this->numPoints = 0;
}

Polynomial::Polynomial(FPolynomialPoint* points, uint32_t numPoints)
{
	this->points = points;
	this->capacity = numPoints;
	this->numPoints = numPoints;
}

Polynomial::Polynomial(FPolynomialPoint* points, uint32_t numPoints, uint32_t capacity)
{
	this->points = points;
	this->capacity = capacity;
	this->numPoints = numPoints;
}

Polynomial::Polynomial(const std::string& str)
{
	// Get Num Points
	this->numPoints = LString::NumOfChars(str, ' ') + 1;
	this->capacity = numPoints;
	this->points = new FPolynomialPoint[capacity];

	// Parse Points
	size_t lastSpace = 0;
	size_t lastX = 0;
	size_t lastCarrot = 0;
	uint32_t currentPointIndex = 0;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == 'x')
		{
			lastX = i;
			points[currentPointIndex].coefficient = LString::SubstrToFloat(str, lastSpace, i);
		}
		else if (str[i] == ' ')
		{
			lastSpace = i;
			points[currentPointIndex].power = LString::SubstrToInt(str, lastCarrot, i);
			currentPointIndex++;
		}
		else if (str[i] == '^')
		{
			lastCarrot = i;
		}
	}
}

std::string Polynomial::ToString() const
{
	std::string str = "";

	for (uint32_t i = 0; i < numPoints; i++)
	{
		str += LString::FloatToString(points[i].coefficient);
		if (points[i].power != 0)
		{
			str += "x";
			if (points[i].power != 1)
			{
				str += "^" + std::to_string(points[i].coefficient);
			}
		}

		if (i != numPoints - 1)
		{
			str += " ";
		}
	}

	return str;
}

float Polynomial::Get(float x) const
{
	float y = 0;
	for (uint32_t i = 0; i < numPoints; i++)
	{
		y += points[i].coefficient * LMath::Pow((float)x, (int)points[i].power);
	}
	return y;
}
