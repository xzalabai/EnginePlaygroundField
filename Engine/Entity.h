#pragma once
#include "Vec2.h"
#include "Colors.h"
#include "Drawable.h"
#include <vector>

using namespace std;
class Entity
{
public:
	Entity(vector<Vec2<float>> model, Vec2<float> position, Color color = Colors::White) :
		model(std::move(model)),
		position(std::move(position)),
		color(color)
	{};
	void TranslateBy(const Vec2<float> offset)
	{
		position += offset;
	}
	void SetScale(const float newScale)
	{
		scale = newScale;
	}
	void SetPosition(const Vec2<float>& newPosition)
	{
		position = newPosition;
	}
	void SetModel(vector<Vec2<float>> newModel)
	{
		model = move(newModel);
	}
	void SetColor(const Color& newColor)
	{
		color = newColor;
	}
	float GetScale() { return scale; };
	Vec2<float> GetPosition() { return position; };
	Drawable GetDrawable() const
	{
		Drawable drw(model, color);
		drw.Scale(scale);
		drw.Translate(position);
		return drw;
	}
public:
	vector<Vec2<float>> model;
	Vec2<float> position{ 0.0f, 0.0f };
	float scale = 1.0f;
	float angle;
	Color color;
};	