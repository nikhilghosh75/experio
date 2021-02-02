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
