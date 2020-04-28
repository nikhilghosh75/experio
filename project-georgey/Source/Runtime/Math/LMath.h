#pragma once

const static float PI = 3.1415926536f;
const static float HALFPI = 1.570796327;

class LMath
{
public:
	static float Abs(float x);

	static float Acos(float x);

	static float Asin(float x);

	static float Atan(float x);

	static float Atan2(float x);
	
	static int Ceil(float f);

	static float Clamp(float f, float min, float max);

	static float ClampAngleDeg(float f);

	static float ClampAngleRad(float f);

	static float Cos(float angle);

	static float DegreesToRadians(float degrees);

	static int Floor(float f);

	static float Lerp(float a, float b, float t);

	static float Ln(float x);

	static float Max(float a, float b);

	static float Min(float a, float b);

	static float Pow(float base, int exponent);

	static float PowE(float exponent);

	static long long PowOfTwo(int e);

	static float RadiansToDegrees(float radians);

	static int Round(float f);

	static float Sin(float angle);

	static float Sqrt(float x);

	static float Tan(float angle);
};