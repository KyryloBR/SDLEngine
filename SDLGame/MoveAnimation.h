#ifndef MOVE_ANIMATION_H_
#define MOVE_ANIMATION_H_

#include "Animation.h"
#include "GraphicsFunction.h"

class MoveAnimation : public Animation
{
public:
	MoveAnimation(const std::string & animationID) : Animation(animationID), m_bReverse(false) {}
	void setBeginPosition(Vector2D * _from);
    void setEndPosition(Vector2D * _to);
	virtual void update();
	void setFunction(GraphicFunction * _function)
	{
		m_function = _function;
	}
	void setReverse(bool _reverse) { m_bReverse = _reverse; }

	Vector2D * getBeginPosition() { return m_beginPosition; }
	Vector2D * getEndPosition() { return m_endPosition; }

	void setDuration(int _duration);
	// Set duration in seconds.
private:
	Vector2D * m_beginPosition;
	Vector2D * m_endPosition;
	Vector2D * m_currentPosition;
	int m_duration;
	float m_velocity;
	bool m_bReverse;
	GraphicFunction *m_function;
};

#endif // MOVE_ANIMATION_H_