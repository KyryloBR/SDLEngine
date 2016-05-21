#include "Weapon.h"
#include "Game.h"
#include "AnimationParser.h"

void Weapon::load(const LoaderParams * pParams)
{
	EGameObject::load(pParams);
	AnimationParser parser;
	parser.parseAnimation(m_animations, "../Data/animation.xml", getType());
}

void Weapon::update()
{
	if (m_pCurrentAnimation)
	{
		m_pCurrentAnimation->update();
	}
}

void Weapon::draw()
{
	if (m_bRendering)
	{
		if (m_pCurrentAnimation->isPlay())
		{
			TextureManager::Instance()->draw(m_pCurrentAnimation->getCurrentId(), (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_alpha, m_angle,
				Game::Instance()->getRenderer(), m_nFlip);
		}
		else
		{
			TextureManager::Instance()->draw(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_alpha, m_angle,
				Game::Instance()->getRenderer(), m_nFlip);
		}
	}
}

void Weapon::clean()
{
	if (m_pCurrentAnimation)
	{
		delete m_pCurrentAnimation;
	}
}