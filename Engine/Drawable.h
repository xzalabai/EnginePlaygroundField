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
		gfx.DrawPolyLine(*model, transform, color);
	}
	void ApplyTransformation(const Mat<float>& tr)
	{
		transform = tr * transform;
	}
private:
	Color color;
	const vector<Vec2<float>>* model;
	Mat<float> transform = Mat<float>::Identity();
};
