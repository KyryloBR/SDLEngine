#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include "stdafx.h"

class Vector2D
{
private:
	float m_x;
	float m_y;

public:
	Vector2D(float _x = 0.0, float _y = 0.0) : m_x(_x), m_y(_y) {}
	Vector2D(const Vector2D & _copyInstance)
	{
		m_x = _copyInstance.m_x;
		m_y = _copyInstance.m_y;
	}

	float getX() const { return m_x; }
	float getY() const { return m_y; }

	void setX(float _x) { m_x = _x; }
	void setY(float _y) { m_y = _y; }

	float length() { return sqrt(m_x * m_x + m_y * m_y); }
	void normalize() 
	{
		float l = length();
		if (l > 0)
		{
			(*this) *= 1 / l;
		}
	}

	Vector2D operator+(Vector2D & _vectorAdd)
	{
		return Vector2D(m_x + _vectorAdd.m_x, m_y + _vectorAdd.m_y);
	}
	friend Vector2D & operator+=(Vector2D & _vector1, Vector2D & _vector2)
	{
		_vector1.m_x += _vector2.m_x;
		_vector1.m_y += _vector2.m_y;

		return _vector1;
	}

	Vector2D operator-(Vector2D & _vectorSub)
	{
		return Vector2D(m_x - _vectorSub.m_x, m_y - _vectorSub.m_y);
	}
	friend Vector2D & operator-=(Vector2D & _vector1, Vector2D & _vector2)
	{
		_vector1.m_x -= _vector2.m_x;
		_vector1.m_y -= _vector2.m_y;

		return _vector1;
	}

	Vector2D operator*(float scalar)
	{
		return Vector2D(m_x * scalar, m_y * scalar);
	}
	Vector2D & operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;

		return *this;
	}

	Vector2D operator/(float scalar)
	{
		return Vector2D(m_x / scalar, m_y / scalar);
	}
	Vector2D & operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;

		return *this;
	}
};

#endif // VECTOR2D_H_