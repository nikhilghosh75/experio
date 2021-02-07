#include "Bezier.h"

#define PB_BEZIER_DEFAULT_CAPACITY 4

Bezier::Bezier()
{
	this->points = new BezierPoint[PB_BEZIER_DEFAULT_CAPACITY];
	this->numPoints = 0;
	this->capacity = PB_BEZIER_DEFAULT_CAPACITY;
}

Bezier::Bezier(uint32_t capacity)
{
	this->points = new BezierPoint[capacity];
	this->numPoints = 0;
	this->capacity = capacity;
}

Bezier::Bezier(BezierPoint * points, uint32_t numPoints)
{
	this->points = new BezierPoint[numPoints];
	memcpy(this->points, points, sizeof(BezierPoint) * numPoints);
	this->numPoints = numPoints;
	this->capacity = numPoints;
}

Bezier::Bezier(BezierPoint * points, uint32_t numPoints, uint32_t capacity)
{
	this->points = new BezierPoint[capacity];
	memcpy(this->points, points, sizeof(BezierPoint) * capacity);
	this->numPoints = numPoints;
	this->capacity = capacity;
}

Bezier::~Bezier()
{
	delete this->points;
}

float Bezier::Get(float x) const
{
	uint32_t currentIndex = GetIndex(x);

	const BezierPoint& point = points[currentIndex];

	float minX = point.startX;
	float maxX = point.endX;

	float t = (x - minX) / (maxX - minX);
	float t2 = t * t;
	float t3 = t2 * t;

	float q = 1 - t;
	float q2 = q * q;
	float q3 = q2 * q;

	return q3 * point.startY + 3 * q2 * t * point.startControlY 
		+ 3 * q * t2 * point.endControlY + t3 * point.endY;
}

void Bezier::Resize(uint32_t newCapacity)
{
	BezierPoint* newData = new BezierPoint[newCapacity];

	for (int i = 0; i < numPoints; i++)
	{
		newData[i] = std::move(points[i]);
	}

	delete[] this->points;
	this->points = newData;
	this->capacity = newCapacity;
}

void Bezier::Insert(float startX, float startY, float endX, float endY)
{
	if (numPoints == capacity)
	{
		Resize(capacity + 10);
	}
}

uint32_t Bezier::GetIndex(float x) const
{
	uint32_t min = 0, max = numPoints;
	while (true)
	{
		uint32_t currentIndex = (min + max) / 2;
		const BezierPoint& currentPoint = this->points[currentIndex];
		if (currentPoint.startX < x && currentPoint.endY > x)
		{
			return currentIndex;
		}

		if (currentPoint.startX < x)
		{
			min = currentIndex;
		}
		else if (currentPoint.endY < x)
		{
			max = currentIndex;
		}
	}
}
