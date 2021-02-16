#pragma once
#include <stdint.h>
#include "FVector2.h"

// Implements a Cubic Bezier Point

class BezierPoint
{
public:
	float startX;
	float startY;
	float endX;
	float endY;
	float startControlX;
	float startControlY;
	float endControlX;
	float endControlY;

	BezierPoint();
	BezierPoint(float startX, float startY, float endX, float endY);
};

class Bezier
{
	BezierPoint* points;
	uint32_t numPoints;
	uint32_t capacity;

public:
	Bezier();
	Bezier(uint32_t capacity);
	Bezier(BezierPoint* points, uint32_t numPoints);
	Bezier(BezierPoint* points, uint32_t numPoints, uint32_t capacity);

	~Bezier();

	float Get(float x) const;
	
	uint32_t Count() const { return numPoints; }
	uint32_t Capacity() const { return capacity; }

	void Resize(uint32_t newCapacity);

	void Insert(float startX, float startY, float endX, float endY);
	void Insert(float startX, float startY, float endX, float endY,
		float startControlX, float startControlY, float endControlX, float endControlY);
	void Insert(FVector2 start, FVector2 end);
	void Insert(FVector2 start, FVector2 end, FVector2 startControl, FVector2 endControl);

	float MinX() const;
	float MaxX() const;

private:
	uint32_t GetIndex(float x) const;

	void Shift(int position = 0, int shift = 1);

	void Remove(uint32_t index);
};

class BezierIterator
{
	Bezier* curve;
	uint32_t currentIndex;

	float x;
	float y;
public:

};

float RiemannSum(const Bezier& curve, float delta = 0.01f);