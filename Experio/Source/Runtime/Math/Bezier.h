#pragma once
#include <stdint.h>
#include "FVector2.h"

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

	void Insert(float startX, float startY, float endX, float endY);
	void Insert(float startX, float startY, float endX, float endY,
		float startControlX, float startControlY, float endControlX, float endControlY);
	void Insert(FVector2 start, FVector2 end);
	void Insert(FVector2 start, FVector2 end, FVector2 startControl, FVector2 endControl);

private:
	uint32_t GetIndex(float x) const;
};

class BezierIterator
{
	Bezier* curve;
	uint32_t currentIndex;

	float x;
	float y;
public:


};