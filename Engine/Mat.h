#pragma once
#include "Vec2.h"
#include "Vec3.h"

template <typename T>
class Mat
{
public:
	Vec2<T> operator*(const Vec2<T> rhs)
	{
		return Vec2<T>(*this * (Vec3<T>) rhs);
	}

	Vec3<T> operator*(const Vec3<T> rhs)
	{
		Vec3<T> newVector;
		newVector.SetX(cell[0][0] * rhs.X() + cell[0][1] * rhs.Y() + cell[0][2] * rhs.W());
		newVector.SetY(cell[1][0] * rhs.X() + cell[1][1] * rhs.Y() + cell[1][2] * rhs.W());
		newVector.SetW(cell[2][0] * rhs.X() + cell[2][1] * rhs.Y() + cell[2][2] * rhs.W());
		return newVector;
	}
	Mat<T> operator*(const Mat<T> rhs) const
	{
		Mat<T> out;
		for (int row_left = 0; row_left < 3; ++row_left)
		{
			for (int col_right = 0; col_right < 3; ++col_right)
			{
				out.cell[row_left][col_right] = (T)0;
				for (int i = 0; i < 3; ++i)
				{
					out.cell[row_left][col_right] += cell[row_left][i] * rhs.cell[i][col_right];
				}
			}
		}
		return out;
	}
	static Mat Scale(T factor)
	{
		return
		{
			(T)factor, (T)0, (T)0,
			(T)0, (T)factor, (T)0,
			(T)0, (T)0, (T)1,
		};
	}
	static Mat Identity()
	{
		return Scale((T)1);
	}
	static Mat FlipY()
	{
		return
		{
			(T)1,(T)0, (T)0,
			(T)0, (T)-1, (T)0,
			(T)0, (T)0, T(1),
		};
	}

	static Mat ScaleIndependent(float x, float y)
	{
		return
		{
			(T)x,(T)0, (T)0,
			(T)0, (T)y, (T)0,
			(T)0, (T)0, T(1),
		};
	}

	static Mat Translate(Vec2<T> vec)
	{
		return
		{
			(T)1,(T)0, (T)vec.X(),
			(T)0, (T)1, (T)vec.Y(),
			(T)0, (T)0, T(1),
		};
	}

	static Mat Rotate(T angle)
	{
		const T cos_ = std::cos(angle);
		const T sin_ = std::sin(angle);
		return
		{
			cos_,	-sin_,	(T)0,
			sin_,	cos_,	(T)0,
			(T)0,		(T)0,		(T)1
		};
	}
public:
	T cell[3][3];
};
