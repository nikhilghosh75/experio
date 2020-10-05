#pragma once

const static float PI = 3.1415926536f;
const static float HALFPI = 1.570796327;
const static float TWOPI = 6.283185307;
const static float ROOTPI = 1.77245385;
const static float QUARTERPI = 0.785398163;
const static float ONEOVERPI = 0.318309886;
const static float E = 2.718281828;
const static float GOLDENRATIO = 1.6180339887;

// All Trig functions are in radians
class LMath
{
public:
	static float Abs(float x);
	static int Abs(int x);

	static float Acos(float x);

	static bool ApproxEquals(float a, float b, float tolerance = 0.0000001);

	static float Asin(float x);

	static float Atan(float x);

	static float Atan2(float x, float y);

	static bool Between(float min, float max, float f);

	static int BinomialCoefficent(int n, int k);
	
	static int Ceil(float f);

	static float Clamp(float f, float min, float max);

	static float ClampAngleDeg(float f);

	static float ClampAngleRad(float f);

	static float CopySign(float x, float y);

	static float Cos(float angle);

	static float CosH(float angle);

	static float Csc(float angle);

	static float DegreesToRadians(float degrees);

	static long long Factorial(unsigned short n);

	static long long Fib(int n);

	static int Floor(float f);

	static float FMod(float x, float y);

	static int GCD(int a, int b);

	static int LCM(int a, int b);

	static float Lerp(float a, float b, float t);

	static float Ln(float x);

	static float Log(float x, float b = 10);

	static float Max(float a, float b);
	static int Max(int a, int b);

	static float Min(float a, float b);
	static int Min(int a, int b);

	static float Pow(float base, float exponent);

	static float Pow(float base, int exponent);

	static float PowE(float exponent);

	static long long PowOfTwo(int e);

	static long long PowOfTen(int e);

	static float RadiansToDegrees(float radians);

	static int Round(float f);

	static float Sec(float angle);

	static float Sin(float angle);

	static float SinH(float angle);

	static float Sqrt(float x);

	static float Tan(float angle);

	static float TanH(float angle);
};