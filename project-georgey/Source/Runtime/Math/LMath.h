#pragma once

const static float PI = 3.141592f;

class LMath
{
public:
	static float Abs(float x);

	static float Cos(float angle);

	static float DegreesToRadians(float degrees);

	static float Ln(float x);

	static float PowE(float exponent);

	static float Pow(float base, int exponent);

	static float RadiansToDegrees(float radians);

	static float Sin(float angle);

	static float Sqrt(float x);

	static float Tan(float angle);
};