#pragma once

template <typename T>
class Vec2
{
public:
	Vec2(T x, T y) :
		x(x), y(y)
	{}

	T X() const { return x; }
	T Y() const { return y; }
	void SetX(T newX) { x = newX; }
	void SetY(T newY) { y = newY; }

	Vec2& operator+=(const Vec2& rhs)
	{
		x = x + rhs.X();
		y = y + rhs.Y();

		return *this;
	}

	Vec2& operator-=(const Vec2& rhs)
	{
		x = x - rhs.X();
		y = y - rhs.Y();

		return *this;
	}

	Vec2 operator-(const Vec2& rhs) const
	{
		return Vec2(*this) -= rhs;
	}

	Vec2 operator*(const T multiplier) const
	{
		Vec2 tmp = *this;
		return (tmp*=multiplier);
	}

	Vec2& operator*=(const T multiplier)
	{
		x = x * multiplier;
		y = y * multiplier;

		return *this;
	}

	T dot(const Vec2& rhs) const
	{
		return (x* rhs.x + y * rhs.y);
	}

	T LengthSquared() const
	{
		return x * x + y * y;
	}

	T Length() const
	{
		return sqrt(LengthSquared());
	}
	Vec2& Rotate(const T angle)
	{
		const T cosTheta = cos(angle);
		const T sinTheta = sin(angle);
		
		const T newX = x * cosTheta - y * sinTheta;
		const T Y = x * sinTheta + y * cosTheta;
		x = newX;
		y = Y;
		return *this;
	}
	Vec2& GetRotated(const T angle)
	{
		return Vec2(*this).Rotate(angle);
	}

	Vec2& Normalize()
	{
		const T length = Length();
		x /= length;
		y /= length;
		return *this;
	}

	Vec2 GetNormalized() const
	{
		Vec2 tmp = *this;
		return tmp.Normalize();
	}

private:
	T x;
	T y;
};