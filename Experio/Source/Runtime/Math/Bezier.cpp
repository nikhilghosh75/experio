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
		bool approx = LMath::ApproxEquals(endX, minX, 0.001f);
		int step = approx ? 1 : 2;
		Shift(0, step);

		points[0] = BezierPoint(startX, startY, endX, endY);
		numPoints++;
		if (!approx)
		{
			points[1] = BezierPoint(endX, endY, points[1].startX, points[1].startY);
			numPoints++;
		}
	}

	// Case 3: Point inserted is greater than the maximum
	if (startX > maxX)
	{
		// If max and start are approximately equal, we only need to insert one point
		bool approx = LMath::ApproxEquals(startX, maxX, 0.001f);
		if (approx)
		{
			points[numPoints] = BezierPoint(startX, startY, endX, endY);
			numPoints++;
		}
		else
		{
			points[numPoints] = BezierPoint(points[numPoints - 1].endX, points[numPoints - 1].endY, startX, startY);
			points[numPoints + 1] = BezierPoint(startX, startY, endX, endY);
			numPoints += 2;
		}
	}

	// Default Case: Must be inserted between two points
	uint32_t startIndex = GetIndex(startX);
	uint32_t endIndex = GetIndex(endX);

	// If start and end points are the same, only need to split one point
	if (startIndex == endIndex)
	{
		BezierPoint& currentPoint = points[startIndex];

		// If current start and start are the same and current end and end are the same, replace point
		if (LMath::ApproxEquals(currentPoint.startX, startX, 0.001f) 
			&& LMath::ApproxEquals(currentPoint.endX, endX, 0.001f))
		{
			currentPoint.startY = startY;
			currentPoint.endY = endY;
		}
		// If starts are equal, break a point into 2
		else if (LMath::ApproxEquals(currentPoint.startX, startX, 0.001f))
		{
			currentPoint.startX = endX;
			currentPoint.startY = endY;
			Shift(startIndex, 1);
			points[startIndex] = BezierPoint(startX, startY, endX, endY);
			numPoints++;
		}
		// If ends are equals, break the point into 2
		else if (LMath::ApproxEquals(currentPoint.endX, endX, 0.001f))
		{
			currentPoint.endX = startX;
			currentPoint.endY = startY;
			Shift(startIndex + 1, 1);
			points[startIndex + 1] = BezierPoint(startX, startY, endX, endY);
			numPoints++;
		}
		// Otherwise, split the point into 3
		else
		{
			currentPoint.endX = startX;
			currentPoint.endY = startY;
			Shift(startIndex + 1, 2);
			points[startIndex + 1] = BezierPoint(startX, startY, endX, endY);
			points[startIndex + 2] = BezierPoint(endX, endY, points[startIndex + 3].startX, points[startIndex + 3].startY);
			numPoints += 2;
		}
	}
	// Otherwise, it will be complicated
	else
	{

	}
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

void Bezier::Shift(int position, int shift)
{
	for (int i = numPoints - 1; i >= position; i--)
	{
		points[i + shift] = points[i];
	}
}
