#ifndef GRAPHICS_FUNCTION_H_
#define GRAPHICS_FUNCTION_H_

#include "Vector2D.h"

class GraphicFunction
{
public:
	virtual void operator()(Vector2D * m_value) = 0;
};

class StraightYConst : public GraphicFunction
{
public:
	StraightYConst() : GraphicFunction() {}
	void operator()(Vector2D * m_value)
	{
		m_value->setY((0 * m_value->getX()) + m_value->getY());
	}
};

class Straight : public GraphicFunction
{
public:
	Straight() : GraphicFunction() {}
	void operator()(Vector2D * m_value)
	{
		m_value->setY(m_value->getX());
	}
};

class Parabola : public GraphicFunction
{
public:
	Parabola() : GraphicFunction() {}
	void operator()(Vector2D * m_value)
	{
		m_value->setY(pow(m_value->getX(), 2));
	}
};

class Hyperbole : public GraphicFunction
{
public:
	Hyperbole() : GraphicFunction() {}
	void operator()(Vector2D * m_value)
	{
		m_value->setY(1 / m_value->getX());
	}
};

class CubicParabola : public GraphicFunction
{
public:
	CubicParabola() : GraphicFunction() {}
	void operator()(Vector2D * m_value)
	{
		m_value->setY(pow(m_value->getX(), 3));
	}
};

#endif // GRAPHICS_FUNCTION_H_