#include "SheetAnimation.h"

void SheetAnimation::update()
{
	if (m_bRunning)
	{
		m_nCurrentFrame++;
		if (m_bAlways)
		{
			if (m_nCurrentFrame == m_nNumFrames)
			{
				m_nCurrentFrame = 0;
			}
		}
	}
	if (m_bStop)
	{
		m_nCurrentFrame = 1;
	}
}


void SheetAnimation::setNumLoop(int _loop)
{
	m_nLoop = _loop;
}

void SheetAnimation::setReverse(bool _reverse)
{
	m_bReverse = _reverse;
}

void SheetAnimation::setAlways(bool _always)
{
	m_bAlways = _always;
}