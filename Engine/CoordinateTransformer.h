#pragma once
#include "Entity.h"
#include "Graphics.h"
#include "Drawable.h"


class CoordinateTransformer
{
public:
	CoordinateTransformer(Graphics& gfx) : gfx(gfx) {}
	void Draw(Drawable &dwb)
	{
		// get the middle of the screen
		Vec2<float> offset{ Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2 };
		dwb.ApplyTransformation(Mat<float>::Translate(offset) * Mat<float>::ScaleIndependent(1, -1));
		//dwb.ScaleSeparately(1, -1);
		//dwb.Translate(offset);
		dwb.Render(gfx);
	}
private:
	Graphics& gfx;
};