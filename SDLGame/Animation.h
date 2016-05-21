#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "stdafx.h"
#include "Vector2D.h"
#include "GameObject.h"


class Animation
{
public:
	Animation(const std::string & animationID) : m_animationID(animationID),m_bStop(true) {}
	std::string getID() { return m_animationID; }
	virtual void play()
	{
		if (m_bStop)
		{
			m_bPause = false;
			m_bStop = false;
			m_bRunning = true;
		}
		else
		{
			m_bPause = false;
			m_bRunning = true;
		}
	}
	virtual void pause()
	{
		m_bRunning = false;
		m_bPause = true;
	}
	virtual void stop()
	{
		m_bStop = true;
		m_bPause = false;
		m_bRunning = false;
	}
	virtual void setParent(GameObject * parent)
	{
		m_objectAnimation = parent;
	}

	virtual void update() = 0;

	bool isPlay() { return m_bRunning; }
	bool isPause() { return m_bPause; }
	bool isStop() { return m_bStop; }

protected:
	std::string m_animationID;
	GameObject *m_objectAnimation;
	bool m_bRunning;
	bool m_bPause;
	bool m_bStop;
};

#endif // ANIMATION_H_