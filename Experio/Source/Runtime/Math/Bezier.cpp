#include "Bezier.h"
#include "LMath.h"

#define PB_BEZIER_DEFAULT_CAPACITY 4

BezierPoint::BezierPoint()
{
	this->startX = 0;
	this->startY = 0;
	this->startControlX = 0;
	this->startControlY = 0;
	this->endControlX = 0;
	this->endControlY = 0;
	this->endX = 0;
	this->endY = 0;
}

BezierPoint::BezierPoint(float startX, float startY, float endX, float endY)
{
	this->startX = startX;
	this->startY = startY;
	this->startControlX = startX;
	this->startControlY = startY;
	this->endControlX = endX;
	this->endControlY = endY;
	this->endX = endX;
	this->endY = endY;
}

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
	if (numPoints + 2 >= capacity)
	{
		Resize(capacity + 10);
	}

	// Case 1: No points currently in vector, insert one
	if (numPoints == 0)
	{
		points[0] = BezierPoint(startX, startY, endX, endY);
		numPoints++;
		return;
	}

	float minX = MinX(), maxX = MaxX();
	// Case 2: Point inserted is less than the minimum
	// If so, shift all elements by one or two
	if (endX < minX)
	{
		// If min and end are approximately equal, we only need to insert one point
		bool approx = LMath::ApproxEquals(endX, minX, 0.0001f);
		int step = approx ? 1 : 2;

		for (int i = numPoints - 1; i >= 0; i--)
		{
			points[i + step] = points[i];
		}

		points[0] = BezierPoint(startX, startY, endX, endY);
		if (!approx)
		{
			points[1] = BezierPoint(endX, endY, points[1].startX, points[1].startY);
		}
	}

	// Case 3: Point inserted is greater than the maximum

	// Default Case: Must be inserted between two points
}

void Bezier::Insert(FVector2 start, FVector2 end)
{
	Insert(start.x, start.y, end.x, end.y);
}

float Bezier::MinX() const
{
	if (numPoints == 0)
		return 0;
	return points[0].startX;
}

float Bezier::MaxX() const
{
	if (numPoints == 0)
		return 0;
	return points[numPoints - 1].endX;
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
