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
	void SetAngle(float newAngle)
	{
		angle = newAngle;
	}
	float GetAngle()
	{
		return angle;
	}
	void SetPosition(Vec2<float> newPosition)
	{
		position = newPosition;
	}
	void TranslateBy(Vec2<float> offset)
	{
		offset = offset.Rotate(-GetAngle());
		position += offset;
	}
	void Draw(Drawable& drw)
	{
		Vec2<float> ng = position * (-1);
		drw.ApplyTransformation(Mat<float>::Scale(scale) * Mat<float>::Rotate(angle) * Mat<float>::Translate(ng));
		ct.Draw(drw);
	}

private:
	Vec2<float> position = { 0,0 };
	float scale = 1.0f;
	float angle = 0;
	CoordinateTransformer ct;


};