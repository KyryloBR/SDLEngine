#include "Decoration.h"
#include "Game.h"
#include "AnimationParser.h"

void Decoration::load(const LoaderParams * pParams)
{
	EGameObject::load(pParams);
	m_pCurrentAnimation = new LoopAnimation(pParams->getTextureID());
	AnimationParser parser;
	parser.parseAnimation(m_pCurrentAnimation, "../Data/animation.xml");
	m_pCurrentAnimation->setLoopAlways(true);
	m_pCurrentAnimation->play();
}

void Decoration::draw()
{
	TextureManager::Instance()->draw(m_pCurrentAnimation->getCurrentId(), (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_alpha, m_angle,
		Game::Instance()->getRenderer(), m_nFlip);
}

void Decoration::update()
{
	m_pCurrentAnimation->update();
}