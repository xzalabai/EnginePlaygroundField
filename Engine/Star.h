#pragma once
#include "Entity.h"
#include "Rect.h"

class Star : public Entity
{
public:
	Star(vector<Vec2<float>> model, Vec2<float> position, float minRadius, float maxRadius, float speed, Color color = Colors::White)
		:
		Entity(model, position, color),
		boundingBox(position, maxRadius),
		maxRadius(maxRadius),
		minRadius(minRadius),
		speed(speed),
		originalColor(color)
	{

	}
	void Update(float dt)
	{
		time += dt;

		float newScale = minRadius + (float)(1 + sin(time * speed)) * (maxRadius - minRadius) / 2;
		SetScale(newScale);

		int newColorR = (int) (originalColor.GetR() + (int)(1 + sin(time * speed)) * (255.0f - originalColor.GetR()) / 2.0f);
		int newColorG = (int) (originalColor.GetG() + (int)(1 + sin(time * speed)) * (255.0f - originalColor.GetG()) / 2.0f);
		int newColorB = (int) (originalColor.GetB() + (int)(1 + sin(time * speed)) * (255.0f - originalColor.GetB()) / 2.0f);

		SetColor(Color(newColorR, newColorG, newColorB));
	}

	void SetPosition(const Vec2<float>& newPosition)
	{
		boundingBox.SetPosition(newPosition, maxRadius);
		Entity::SetPosition(newPosition);
	}
public: // TODO: Change to private
	Rect boundingBox;
	Color originalColor;
	float maxRadius = 0;
	float minRadius = 0;
	float speed = 0;
	float time = 0;
};