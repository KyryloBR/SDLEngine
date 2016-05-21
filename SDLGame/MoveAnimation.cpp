#include "MoveAnimation.h"

void MoveAnimation::setBeginPosition(Vector2D * _from)
{
	if (!_from)
	{
		m_beginPosition = m_objectAnimation->getPosition();
	}
	else
	{
		m_beginPosition = _from;
		m_objectAnimation->setPosition(*m_beginPosition);
	}
	m_currentPosition = m_beginPosition;
}

void MoveAnimation::setEndPosition(Vector2D * _to)
{
	m_endPosition = _to;
	if (!m_beginPosition)
	{
		m_beginPosition = m_objectAnimation->getPosition();
		m_currentPosition = m_beginPosition;
	}
	m_velocity = (abs(m_beginPosition->getX()) + abs(m_endPosition->getX())) / (m_duration * 1000);
}

//void MoveAnimation::setFunction(GraphicFunction * _function)
//{
//	m_function = _function;
//}


void MoveAnimation::setDuration(int _duration)
{
	m_duration = _duration;
}


void MoveAnimation::update()
{
	if (m_bRunning)
	{
		m_function->operator()(m_currentPosition);
		m_objectAnimation->setPosition(*m_currentPosition);
		if (m_bReverse)
		{
			m_currentPosition->setX(m_currentPosition->getX() + m_velocity);
		}	
		else
		{
			m_currentPosition->setX(m_currentPosition->getX() + m_velocity);
		}
	}
}