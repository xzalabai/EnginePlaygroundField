/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Colors.h"
#include "Vec2.h"
#include "CustomMath.h"
#include "Entity.h"
#include "StarGenerator.h"
#include "Game.h"
#include "CoordinateTransformer.h"
#include <map>
#include "Mat.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ct(gfx),
	cam(ct)
{
	// BALLS -------------------------------------------------------------------------------
	entities.emplace_back(Entity{ { {80.0f, 20.0f}, {-300.0f, -90.0f }}, {0.0f, 0.0f} });
	//vector<Vec2<float>> ballShape = ;
	Ball b({ 0.0f, 20.0f }, 5, {0,-100});
	balls.emplace_back(b);


	// -------------------------------------------------------------------------------------
	// STARS -------------------------------------------------------------------------------
	// -------------------------------------------------------------------------------------
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(-1500.0, 1500.0);

	for (int i = 0; i < 500; )
	{
		Star newStar = StarGenerator::MakeRandomStar(make_pair(0.0f, 1.0f), make_pair(10.0f, 100.0f), make_pair(1.0f, 6.0f), make_pair(4.0f,8.0f));
		newStar.SetPosition(Vec2<float>((float)dist(mt), (float)dist(mt)));
		bool bOverlap = false;
		for (auto& otherStar : stars)
		{
			if (Rect::doOverlap(
				newStar.boundingBox.GetUpLeft(),
				newStar.boundingBox.GetBottomRight(),
				otherStar.boundingBox.GetUpLeft(),
				otherStar.boundingBox.GetBottomRight()))
			{
				bOverlap = true;
				break;
			}
		}
		if (!bOverlap)
		{
			stars.emplace_back(newStar);
			++i;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	constexpr float speed = 3.0f;
	const float dt = ft.Mark();
	t += dt;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		cam.TranslateBy({0.0f, -speed});
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		cam.TranslateBy({ 0.0f, speed });
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		cam.TranslateBy({ -speed, 0.0});
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		cam.TranslateBy({ speed, 0.0f});
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		cam.SetScale(cam.GetScale() * 0.95f);
	}
	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		cam.SetScale(cam.GetScale() * 1.05f);
	}
	if (wnd.kbd.KeyIsPressed('Q'))
	{
		cam.SetAngle(cam.GetAngle() + 0.11f * dt);
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		cam.SetAngle(cam.GetAngle() - 0.11f * dt);
	}

	// PLANK
	//Entity& plank = *entities.begin();
	//Vec2<float> dir = plank.model.back() - plank.model.front();
	//for (auto& b : balls)
	//{
	//	b.Update(dt);
	//	if (DistancePointToLine<float>(plank.model.front(),
	//		plank.model.back(), b.GetPosition()) < b.GetRadius())
	//	{
	//		const Vec2<float> w = dir.GetNormalized();
	//		const Vec2<float> v = b.GetVelocity();
	//		b.SetVelocity(w * (v.dot(w)) * 2.0f - v);
	//	}
	//}

	// STARS ------------------------------
	for (auto& s : stars)
	{
		s.Update(dt);
	}

	// ROTATING STAR
	/*rotatingStar = StarGenerator::MakeStar(10, 4);
	const float theta = PI * t;
	for (auto& pt : rotatingStar)
	{
		pt.Rotate(theta);
	}*/
}

void Game::ComposeFrame()
{
	// PLANK
	//CoordinateTransformer ct{ gfx };
	//for (auto& e : entities)
	//{
	//	cam.Draw(e.GetDrawable());
	//}

	// BALLS ----------------------------------
	//for (auto& b : balls)
	//{
	//	cam.Draw(b.GetDrawable());
	//}

	// ----------------------------------------
	// STARS ----------------------------------
	// ----------------------------------------

	for (auto& s : stars)
	{
		//vector<Vec2<float>> rect = s.boundingBox.GetAllPoints();
		//Entity m{ rect, {0.0, 0.0} };
		//cam.Draw(m.GetDrawable());
		cam.Draw(s.GetDrawable());
	}


	//ROTATING STAR
	//cam.Draw(Drawable(rotatingStar));


//	 STATIC STAR WITH MATRIX
	//Mat<float> x = Mat<float>::Scale(10);
	//Mat<float> y = Mat<float>::Rotate(0.2);
	//Mat<float> w = Mat<float>::Translate(10,10);
	//Mat<float> z = x*y*w;
	//auto star = StarGenerator::MakeStar(5,9,6);
	//for (auto& s : star)
	//{
	//	auto vec3 = (Vec3<float>)s;
	//	s = Vec2<float>(z * s);
	//}
	//cam.Draw(Drawable(star));


}
