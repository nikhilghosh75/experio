#include <limits>
#include <iostream>
#include "math.h"

#include "LMath.h"

using namespace std;

/*
int main()
{
	cout << LMath::Abs(-1.4f) << endl;
	cout << LMath::Sin(1.2f) << endl;
	cout << LMath::Cos(1.3f) << endl;
	cout << LMath::Pow(1.5f, 3) << endl;
	cout << LMath::Sqrt(5.5f) << endl;
	cout << LMath::Ln(512.f) << endl;
}
*/

float LMath::Abs(float x)
{
	if (x < 0)
	{
		return x * -1;
	}
	return x;
}

float LMath::Cos(float angle)
{
	return 1 - Pow(angle, 2) / 2.f + Pow(angle, 4) / 24.f - Pow(angle, 6) / 720.f + Pow(angle, 8) / 40320.f - Pow(angle, 10) / 3628800.f + Pow(angle, 12) / 479001600.f;
}

float LMath::Pow(float base, int exponent)
{
	if (exponent == 0)
	{
		return 1;
	}
	float result = 1.f;
	if (exponent < 0)
	{
		for (int i = 0; i < exponent; i++)
		{
			result /= base;
		}
		return result;
	}
	for (int i = 0; i < exponent; i++)
	{
		result *= base;
	}
	return result;
}

float LMath::Ln(float x)
{
	if(x < 0)
	{
		return std::numeric_limits<float>().infinity();
	}
	return log(x);
}

float LMath::Sin(float angle)
{
	return angle - Pow(angle, 3) / 6.f + Pow(angle, 5) / 120.f - Pow(angle, 7) / 5040.f + Pow(angle, 9) / 362880.f - Pow(angle, 11) / 39916800.f;
}

float LMath::Sqrt(float x)
{
	return sqrt(x);
}

float LMath::Tan(float angle)
{
	if(angle > 1.570795f && angle < 1.570797f)
	{
		return std::numeric_limits<float>().infinity();
	}
	return LMath::Sin(angle)/LMath::Cos(angle);
}