#pragma once

#ifndef __Vector2D__
#define __Vector2D__

#include <math.h>

class Vector2D
{
public:
	Vector2D(float x, float y) : m_X(x), m_Y(y) {}

	float getX() { return m_X; }
	float getY() { return m_Y; }

	void setX(float x) { m_X = x; }
	void setY(float y) { m_Y = y; }

	float length() { return sqrt(m_X * m_X + m_Y * m_Y); }

	Vector2D operator+ (const Vector2D& v2) const
	{
		return Vector2D(m_X + v2.m_X, m_Y + v2.m_Y);
	}

	friend Vector2D& operator+= (Vector2D& v1, const Vector2D& v2)
	{
		v1.m_X += v2.m_X;
		v1.m_Y += v2.m_Y;

		return v1;
	}

	Vector2D operator* (float scalar)
	{
		return Vector2D(m_X * scalar, m_Y * scalar);
	}

	Vector2D& operator*= (float scalar)
	{
		m_X *= scalar;
		m_Y *= scalar;

		return *this;
	}

	Vector2D operator- (const Vector2D & v2) const
	{
		return Vector2D(m_X - v2.m_X, m_Y - v2.m_Y);
	}

	friend Vector2D& operator-= (Vector2D& v1, const Vector2D& v2)
	{
		v1.m_X -= v2.m_X;
		v1.m_Y -= v2.m_Y;

		return v1;
	}

	Vector2D operator/ (float scalar)
	{
		if (scalar == 0)
			return Vector2D(0, 0);

		return Vector2D(m_X / scalar, m_Y / scalar);
	}

	Vector2D& operator/= (float scalar)
	{
		if (scalar == 0)
		{
			m_X = 0;
			m_Y = 0;
		}

		m_X /= scalar;
		m_Y /= scalar;

		return *this;
	}

	void normalize()
	{
		float l = length();
		if (l > 0)
			(*this) *= 1 / l;
	}

private:
	float m_X;
	float m_Y;
};

#endif // __Vector2D__