#pragma once
# include "Vec2.h"
# include "Entity.h"

class Rect
{
public:
	Rect(Vec2<float> center, float radius) :
		radius(radius)
	{
		SetPosition(center, radius);
	}
	static bool doOverlap(Vec2<float> l1, Vec2<float> r1, Vec2<float> l2, Vec2<float> r2)
	{
		// if rectangle has area 0, no overlap
		if (l1.X() == r1.X() || l1.Y() == r1.Y() || r2.X() == l2.X() || l2.Y() == r2.Y())
			return false;

		// If one rectangle is on left side of other
		if (l1.X() > r2.X() || l2.X() > r1.X())
			return false;

		// If one rectangle is above other
		if (r1.Y() > l2.Y() || r2.Y() > l1.Y())
			return false;

		return true;
	}
	vector<Vec2<float>> GetAllPoints()
	{
		vector<Vec2<float>> allPts;
		allPts.reserve(4);
		allPts.emplace_back(upLeft);
		allPts.emplace_back(Vec2<float>{upLeft.X() + radius * 2, upLeft.Y()});
		allPts.emplace_back(bottomRight);
		allPts.emplace_back(Vec2<float>{upLeft.X(), upLeft.Y() - radius * 2});

		return allPts;
	}
	void SetPosition(const Vec2<float>& newCenter, const float newRadius)
	{
		radius = newRadius;
		upLeft = { newCenter.X() - radius, newCenter.Y() + radius };
		bottomRight = { newCenter.X() + radius, newCenter.Y() - radius };
	}
	Vec2<float> GetUpLeft() { return upLeft; }
	Vec2<float> GetBottomRight() { return bottomRight; }
private:
	Vec2<float> upLeft{ 0.0f, 0.0f };
	Vec2<float> bottomRight{ 0.0f, 0.0f };
	float radius;
};