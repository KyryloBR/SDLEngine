#include "AmmoObject.h"
#include "Game.h"

AmmoObject::AmmoObject() : EGameObject()
{
	m_nDamage = 30;
	m_bShooting = false;
	m_bHit = false;
}

void AmmoObject::load(const LoaderParams * pParams)
{
	EGameObject::load(pParams);
}

void AmmoObject::draw()
{
	if (m_velocity.getX() > 0)
	{
		TextureManager::Instance()->draw(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height,
			Game::Instance()->getRenderer());
	}
	else
	{
		TextureManager::Instance()->draw(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height,
			Game::Instance()->getRenderer(),SDL_FLIP_HORIZONTAL);
	}
}

void AmmoObject::update()
{
	//if (m_bShooting)
	//{	
		m_position += m_velocity;
		m_position += m_acceleration;
	//}
}

void AmmoObject::clean()
{
	EGameObject::clean();
}