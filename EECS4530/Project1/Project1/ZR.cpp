#include <iostream>
#include <math.h>

#define PI 3.14159265

struct Point
{
	float x;
	float y;
	float z;

	void set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Triangle
{
	Point p1;
	Point p2;
	Point p3;
};

// set the [iPoint]th point in the raw point data
void setPoint(float *raw, int iPoint, Point point)
{
	float *rawPoint = &(raw[3 * iPoint]);
	rawPoint[0] = point.x;
	rawPoint[1] = point.y;
	rawPoint[2] = point.z;
}

// set the [iTriangle]th triangle in the raw point data
void setTriangle(float *raw, int iTriangle, Triangle triangle)
{
	setPoint(raw, 3 * iTriangle + 0, triangle.p1);
	setPoint(raw, 3 * iTriangle + 1, triangle.p2);
	setPoint(raw, 3 * iTriangle + 2, triangle.p3);
}

// NOTE: ignores topRadius
float *generateCone(float baseRadius, float height, float topRadius, int nbrOfSteps, int &nbrOfValues)
{
	// a triangle for each step
	int numTriangles = nbrOfSteps;

	nbrOfValues = numTriangles * 3 * 3;
	float *points = new float[nbrOfValues];

	// divide base into equal radians
	float radPerDivision = 2 * PI / nbrOfSteps;

	// draw a triangle at each division
	Triangle tri;
	for (int i = 0; i < nbrOfSteps; ++i)
	{
		float rad = i * radPerDivision;

		tri.p1.set(0, 0, 0);
		tri.p2.set(0, height, 0);
		tri.p3.set(cos(rad) * baseRadius, 0, sin(rad) * baseRadius);

		setTriangle(points, i, tri);
	}

	return points;
}
