#pragma once
# include "Vec2.h"
# include "Colors.h"
# include "Graphics.h"
# include <vector>
using namespace std;

class Drawable
{
public:
	Drawable(const vector<Vec2<float>>& model, Color color = Colors::White) :
		model(&model), color(color) {}
	
	void Render(Graphics &gfx)
	{
		vector<Vec2<float>> copy = *model; // TODO MOVE THIS CHUNK TO DrawPolyLine
		for (auto& vertice : copy)
		{
			vertice.SetX(vertice.X() * scaleX);
			vertice.SetY(vertice.Y() * scaleY);
			vertice += translation;
		}
		gfx.DrawPolyLine(copy, color);
	}
	void Translate(const Vec2<float>& newTranslation)
	{
		translation += newTranslation;
	}
	void Scale(float newScale)
	{
		scaleX *= newScale;
		scaleY *= newScale;
		translation *= newScale;
	}
	void ScaleSeparately(float newScaleX, float newScaleY)
	{
		scaleX *= newScaleX;
		scaleY *= newScaleY;

		translation.SetX(translation.X() * newScaleX);
		translation.SetY(translation.Y() * newScaleY);
	}
private:
	Color color;
	const vector<Vec2<float>>* model;
	Vec2<float> translation{0.0f, 0.0f};
	float scaleX = 1;
	float scaleY = 1;
};
