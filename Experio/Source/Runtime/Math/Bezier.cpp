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
	delete[] this->points;
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
		return;
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
		return;
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
		// Remove all points between start and end (exclusive)
		uint32_t difference = endIndex - startIndex - 1;
		for (uint32_t i = 0; i < difference; i++)
		{
			Remove(startIndex + 1);
		}

		// The thing
		Shift(startIndex + 1, 1);
		points[startIndex].endX = startX;
		points[startIndex].endY = startY;
		points[startIndex + 1] = BezierPoint(startX, startY, endX, endY);
		points[startIndex + 2].startX = endX;
		points[startIndex + 2].startY = endY;
		numPoints++;
	}
}

void Bezier::Insert(float startX, float startY, float endX, float endY, float startControlX, float startControlY, float endControlX, float endControlY)
{
	Insert(startX, startY, endX, endY);
	BezierPoint& point = points[GetIndex((startX + endX) / 2.f)];
	point.startControlX = startControlX;
	point.startControlY = startControlY;
	point.endControlX = endControlX;
	point.endControlY = endControlY;
}

void Bezier::Insert(FVector2 start, FVector2 end)
{
	Insert(start.x, start.y, end.x, end.y);
}

void Bezier::Insert(FVector2 start, FVector2 end, FVector2 startControl, FVector2 endControl)
{
	Insert(start.x, start.y, end.x, end.x, startControl.x, startControl.y, endControl.x, endControl.y);
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

float Bezier::Domain() const
{
	if (numPoints == 0)
		return 0;
	return points[numPoints - 1].endX - points[0].startX;
}

float Bezier::MinY() const
{
	if (numPoints == 0)
		return 0;

	float minY = points[0].startY;

	for (uint32_t i = 0; i < numPoints; i++)
	{
		minY = LMath::Min(LMath::Min(points[i].startY, points[i].endY), minY);
	}
	return minY;
}

float Bezier::MaxY() const
{
	if (numPoints == 0)
		return 0;

	float maxY = points[0].startY;

	for (uint32_t i = 0; i < numPoints; i++)
	{
		maxY = LMath::Max(LMath::Max(points[i].startY, points[i].endY), maxY);
	}
	return maxY;
}

float Bezier::Range() const
{
	return MaxY() - MinY();
}

float Bezier::Get(float x, uint32_t currentIndex) const
{
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

uint32_t Bezier::GetIndex(float x) const
{
	uint32_t min = 0, max = numPoints;
	float minX = MinX(), maxX = MaxX();
	if (minX >= x)
		return 0;
	else if (maxX <= x)
		return max - 1;

	while (true)
	{
		uint32_t currentIndex = (min + max) / 2;
		const BezierPoint& currentPoint = this->points[currentIndex];
		if (currentPoint.startX <= x && currentPoint.endX >= x)
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

void Bezier::Remove(uint32_t index)
{
	for (uint32_t i = index; i < numPoints - 1; i++)
	{
		points[i] = points[i + 1];
	}
	numPoints--;
}

BezierIterator::BezierIterator(const Bezier* curve)
{
	this->curve = curve;
	currentIndex = 0;
	x = curve->points[0].startX;
	y = curve->points[0].startY;
}

BezierIterator::BezierIterator(const Bezier* curve, float xStart)
{
	this->curve = curve;
	currentIndex = curve->GetIndex(xStart);
	this->x = xStart;
	this->y = curve->Get(xStart, currentIndex);
}

float BezierIterator::Y() const
{
	return y;
}

float BezierIterator::operator*() const
{
	return y;
}

void BezierIterator::Step(float xStep)
{
	if (xStep <= 0)
		return;

	this->x += xStep;
	if (curve->points[currentIndex].endX < x)
	{
		currentIndex++;
	}
	this->y = curve->Get(x, currentIndex);
}

float RiemannSum(const Bezier& curve, float delta)
{
	unsigned int numIterations = (unsigned int) (curve.Range() / delta);
	BezierIterator it(&curve);

	float sum = 0;
	for (unsigned int i = 0; i < numIterations; i++)
	{
		sum += it.Y() * delta;
		it.Step(delta);
	}

	return sum;
}
