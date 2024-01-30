#pragma once
#include "Vec2.h"

template <typename T>
class Vec3
{
public:
	Vec3() = default;
	Vec3(T x, T y) :
		x(x), y(y)
	{}

	T X() const { return x; }
	T Y() const { return y; }
	T W() const { return w; }
	void SetX(T newX) { x = newX; }
	void SetY(T newY) { y = newY; }
	void SetW(T newW) { w = newW; }

	explicit Vec3(const Vec2<T> vec2) :
		Vec3(vec2.X(), vec2.Y())
	{}

	explicit operator Vec2<T>() const
	{
		return { x, y};
	}

	Vec3& operator+=(const Vec3& rhs)
	{
		x = x + rhs.X();
		y = y + rhs.Y();

		return *this;
	}

	Vec3& operator-=(const Vec3& rhs)
	{
		x = x - rhs.X();
		y = y - rhs.Y();

		return *this;
	}

	Vec3 operator-(const Vec3& rhs) const
	{
		return Vec3(*this) -= rhs;
	}

	Vec3 operator*(const T multiplier) const
	{
		Vec3 tmp = *this;
		return (tmp *= multiplier);
	}

	Vec3& operator*=(const T multiplier)
	{
		x = x * multiplier;
		y = y * multiplier;

		return *this;
	}

	T dot(const Vec3& rhs) const
	{
		return (x * rhs.x + y * rhs.y);
	}

	T LengthSquared() const
	{
		return x * x + y * y;
	}

	T Length() const
	{
		return sqrt(LengthSquared());
	}
	Vec3& Rotate(const T angle)
	{
		const T cosTheta = cos(angle);
		const T sinTheta = sin(angle);

		const T newX = x * cosTheta - y * sinTheta;
		const T Y = x * sinTheta + y * cosTheta;
		x = newX;
		y = Y;
		return *this;
	}
	Vec3& GetRotated(const T angle)
	{
		return Vec3(*this).Rotate(angle);
	}

	Vec3& Normalize()
	{
		const T length = Length();
		x /= length;
		y /= length;
		return *this;
	}

	Vec3 GetNormalized() const
	{
		Vec3 tmp = *this;
		return tmp.Normalize();
	}

private:
	T x;
	T y;
	T w = (T)1;
};