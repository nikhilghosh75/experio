#include <limits>
#include <iostream>
#include "math.h"
#include "LMath.h"

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

const unsigned long long POWOFTEN[] = {
	1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 
	1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 100000000000000000
};

const unsigned long long FIBONACCI[] = {
	0, 1, 1, 2, 3, 5, 8, 13, 21, 34,
	55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181,
	6765, 10946, 17111, 28657, 46368, 75025, 121393, 196418, 317811, 514229,
	832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986,
	102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903, 2971215073, 4807526976, 7778742049,
	12586269025, 20365011074, 32951280099, 53316291173, 86267571272, 139583862445, 225851433717, 365435296162, 591286729879, 956722026041,
	1548008755920, 2504730781961, 4052739537881, 6557470319842, 10610209857723, 17167680177565, 27777890035288, 44945570212853, 72723460248141, 117669030460994
};

float LMath::Abs(float x)
{
	if (x < 0)
	{
		return x * -1;
	}
	return x;
}

float LMath::Acos(float x)
{
	return HALFPI - Asin(x);
}

bool LMath::ApproxEquals(float a, float b, float tolerance)
{
	if (Abs(a - b) < tolerance)
	{
		return true;
	}
	return false;
}

float LMath::Asin(float x)
{
	return x + Pow(x, 3)/6.f + Pow(x, 5) * 3.f/ 40.f + Pow(x, 7) * 15.f / 336.f + Pow(x, 9) * 105.f / 3456.f + Pow(x, 11) * 945.f / 42240.f + Pow(x, 13) * 10395.f / 599040.f + Pow(x, 15) * 135135.f / 9676800.f + Pow(x, 17) * 2027025.f / 175472640.f + Pow(x, 19) * 34459425.f / 3530096640.f + Pow(x, 21) * 654729075.f / 78033715200.f;
}

float LMath::Atan(float x)
{
	float result = 0;
	float power = x;
	short sign = 1;
	for (int i = 1; i < 26; i += 2)
	{
		result += sign * power / (float)i;
		power *= x * x;
		sign *= -1;
	}
	return result;
}

float LMath::Atan2(float x, float y)
{
	if (x == 0.f)
	{
		if (y > 0)
		{
			return HALFPI;
		}
		return -HALFPI;
	}

	float ratio = y / x;
	
	if (x > 0)
	{
		return Atan(ratio);
	}
	if (y > 0)
	{
		return Atan(ratio) + PI;
	}
	return Atan(ratio) - PI;
}

bool LMath::Between(float min, float max, float f)
{
	if (f < max && f > min)
	{
		return true;
	}
	return false;
}

float LMath::Clamp(float f, float min, float max)
{
	if (f < min)
	{
		return min;
	}
	if (f > max)
	{
		return max;
	}
	return f;
}

float LMath::ClampAngleDeg(float f)
{
	return Clamp(f, 0.f, 360.f);
}

float LMath::ClampAngleRad(float f)
{
	return Clamp(f, 0.0f, 2 * PI);
}

float LMath::CopySign(float x, float y)
{
	if (y > 0.0f)
	{
		return LMath::Abs(x);
	}
	return -1.f * LMath::Abs(x);
}

float LMath::Cos(float angle)
{
	return 1 - Pow(angle, 2) / 2.f + Pow(angle, 4) / 24.f - Pow(angle, 6) / 720.f + Pow(angle, 8) / 40320.f - Pow(angle, 10) / 3628800.f + Pow(angle, 12) / 479001600.f - Pow(angle, 14) * 87178291200.f;
}

float LMath::DegreesToRadians(float Degrees)
{
	return Degrees * PI / 180.f;
}

long long LMath::FactorialInt(unsigned short n)
{
	int result = 1;
	for (int i = 2; i < n; i++)
	{
		result *= i;
	}
	return result;
}

long long LMath::Fib(int n)
{
	if (n < 0 || n > 69)
	{
		return 0;
	}
	return FIBONACCI[n];
}

float LMath::Lerp(float a, float b, float t)
{
	return ((b - a) * t) + a;
}

float LMath::Ln(float x)
{
	if (x < 0)
	{
		return std::numeric_limits<float>().infinity();
	}
	return log(x);
}

float LMath::Max(float a, float b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

float LMath::Min(float a, float b)
{
	if (a < b)
	{
		return a;
	}
	return b;
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
	if (e >= 0 && e < 64)
	{
		return POWOFTWO[e];
	}
	return 0;
}

long long LMath::PowOfTen(int e)
{
	if (e < 19 && e >= 0)
	{
		return POWOFTEN[e];
	}
	return 0;
}

float LMath::RadiansToDegrees(float radians)
{
	return radians * 180.f / PI;
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