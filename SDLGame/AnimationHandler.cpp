#include "AnimationHandler.h"
#include "AnimationParser.h"
#include "LoopAnimation.h"

AnimationHandler * AnimationHandler::s_pInstance = 0;

void AnimationHandler::load(const std::string & filename)
{
	m_filename = filename;
	AnimationParser parser;
	parser.parseAnimation(m_animations, m_filename);
}

void AnimationHandler::play(const std::string & _animationID)
{
	m_animations[_animationID]->play();
}

void AnimationHandler::stop(const std::string & _animationID)
{
	m_animations[_animationID]->stop();
}

void AnimationHandler::pause(const std::string & _animationID)
{
	m_animations[_animationID]->pause();
}

void AnimationHandler::setParent(const std::string & _animationID, GameObject * pObject)
{
	m_animations[_animationID]->setParent(pObject);
}

void AnimationHandler::update()
{
	for (std::map<std::string, Animation*>::iterator it = m_animations.begin(); it != m_animations.end(); ++it)
	{
		it->second->update();
	}
}

void AnimationHandler::clearAll()
{
	if (!m_animations.empty())
	{
		m_animations.clear();
	}
}

void AnimationHandler::setAlways(const std::string & _animationID, bool _always)
{
	LoopAnimation * pAnimation = dynamic_cast<LoopAnimation*>(m_animations[_animationID]);
	if (pAnimation)
	{
		pAnimation->setLoopAlways(_always);
	}
}