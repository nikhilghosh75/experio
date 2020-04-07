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

const unsigned long long POWOFTWO[] = {
	1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 
	131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296, 
	8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 281474976710656,
	562949953421312, 1125889906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808
};

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

float LMath::DegreesToRadians(float Degrees)
{
	return Degrees * PI / 180.f;
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

float LMath::RadiansToDegrees(float radians)
{
	return radians * 180.f / PI;
}

float LMath::PowE(float exponent)
{
	float result = 1;
	int factorial = 1;
	for (int i = 1; i < 25; i++)
	{
		factorial *= i;
		result += exponent / factorial;
	}
	return result;
}

long long LMath::PowOfTwo(int e)
{
	if (e > 0 && e < 64)
	{
		return POWOFTWO[e];
	}
	return 0;
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