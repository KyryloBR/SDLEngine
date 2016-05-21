#include "LoopAnimation.h"
#include "TextureManager.h"
#include "Game.h"

void LoopAnimation::addFrame(int i,const std::string & frame)
{
	m_frames.insert(std::make_pair(std::to_string(i), frame));
	TextureManager::Instance()->load(m_animationID + std::to_string(i), frame,
		Game::Instance()->getRenderer());
}

void LoopAnimation::update()
{
	if (m_bRunning)
	{
		if (!m_bLoop)
		{
			if (m_loop >= 0)
			{								
				m_loop--;
			}
		}
		else
		{
			if (m_currentIndex > m_frames.size() - 2)
			{
				m_bStop = true;
			}
			else
			{
				m_currentIndex++;
			}
		}
	}
	else if (m_bStop)
	{
		m_currentIndex = 0;
	}
	SDL_Delay(30);
}

void LoopAnimation::setIndexBegin(int index)
{
	m_currentIndex = index;
}

void LoopAnimation::setLoop(int loop)
{
	m_loop = loop;
}

void LoopAnimation::setLoopAlways(bool loop)
{
	m_bLoop = loop;
}

std::string LoopAnimation::getCurrentId()
{
	return m_animationID + std::to_string(m_currentIndex);
}