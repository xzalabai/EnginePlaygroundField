#pragma once
#include "Vec2.h"
#include "assert.h"
#include "Star.h"
#include "Entity.h"
#include <random>

class StarGenerator
{
public:
	static Star MakeRandomStar(pair<float, float>& radius, pair<float, float>& scale, pair<float, float>& speed, pair<float, float >& polygons)
	{
		std::mt19937 generator(std::random_device{}());

		std::uniform_real_distribution<double> radiusDistr(radius.first, radius.second);
		float inRadius = (float) radiusDistr(generator);
		float outRadius = 1;
		inRadius > outRadius ? swap(inRadius, outRadius) : true;

		std::uniform_real_distribution<double> scaleDistr(scale.first, scale.second);
		float minScale = (float)scaleDistr(generator);
		float maxScale = (float)scaleDistr(generator);
		minScale > maxScale ? swap(minScale, maxScale) : 1;

		std::uniform_real_distribution<double> speedDistr(speed.first, speed.second);
		const float speedD = (float) speedDistr(generator);

		std::uniform_real_distribution<double> polygonsDistr(polygons.first, polygons.second);
		const int polygon = (int) polygonsDistr(generator);

		std::uniform_int_distribution<> colorDistr(0, 254);
		Color c(colorDistr(generator), colorDistr(generator), colorDistr(generator));

		// override
		return Star(MakeStar(outRadius, inRadius, polygon), Vec2<float>{ 0.0f, 0.0f }, minScale, maxScale, speedD, c);
	}

	static vector<Vec2<float>> MakeStar(float outRadius, float inRadius, int polygons = 6)
	{
		/*assert(outRadius >= 0);
		assert(outRadius <= 1);
		assert(inRadius <= 1);
		assert(inRadius >= 0);*/

		vector<Vec2<float>> polygon;
		polygon.reserve(polygons + polygons);
		const float dAngle = 2.0f * 3.14159f / float(polygons * 2);
		for (int i = 0; i < polygons * 2; ++i)
		{
			const float radian = (i % 2 == 0) ? outRadius : inRadius;
			polygon.emplace_back(
				float(radian * cos(float(i) * dAngle)), float(radian * sin(float(i) * dAngle))
			);
		}
		return polygon;
	}

};

