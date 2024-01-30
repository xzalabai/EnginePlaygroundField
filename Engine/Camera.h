#pragma once
#include "Vec2.h"
#include "Entity.h"
#include "Colors.h"
#include "Drawable.h"
#include "CoordinateTransformer.h"


class Camera
{
public:
	Camera(CoordinateTransformer ct) :
		ct(ct)
	{}
	void SetScale(float newScale)
	{
		scale = newScale;
	}
	float GetScale()
	{
		return scale;
	}
	void SetPosition(Vec2<float> newPosition)
	{
		position = newPosition;
	}
	void TranslateBy(Vec2<float> offset)
	{
		position += offset;
	}
	void Draw(Drawable& drw)
	{
		drw.Translate(position * (-1));
		drw.Scale(scale);
		ct.Draw(drw);
	}

private:
	Vec2<float> position = { 0,0 };
	float scale = 1.0f;
	CoordinateTransformer ct;


};