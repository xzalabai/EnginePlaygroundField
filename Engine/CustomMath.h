#pragma once
#include "Vec2.h"

constexpr float PI = 3.1415;

template<typename T>
float DistancePointToLine(Vec2<T>& p0, Vec2<T>& p1, Vec2<T> &q )
{
	auto sq = [](T a) { return a * a; };
	const T a = p0.Y() - p1.Y();
	const T b = p1.X() - p0.X();
	const T c = p0.X() * p1.Y() - p1.X() * p0.Y();

	float dist = std::abs(a * q.X() + b * q.Y() + c) / std::sqrt(sq(a) + sq(b));
	return dist;
}
