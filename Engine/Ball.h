#pragma once
#include "Entity.h"
#include "StarGenerator.h"

class Ball : public Entity
{
public:
	Ball(Vec2<float> velocity, float radius, Vec2<float> position, Color color = Colors::White)
		:
		velocity(velocity),
		radius(radius),
		Entity(StarGenerator::MakeStar(radius, radius, 10), position, color)
	{

	}
	void SetVelocity(Vec2<float> newVelocity)
	{
		velocity = newVelocity;
	}
	Vec2<float> GetVelocity() const
	{
		return velocity;
	}
	float GetRadius() const
	{
		return radius;
	}
	void Update(float dt)
	{
		TranslateBy(velocity * dt);
	}
private:
	Vec2<float> velocity{ 0,0 };
	float radius = 0;
};
