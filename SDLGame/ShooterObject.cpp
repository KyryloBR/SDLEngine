#include "ShooterObject.h"
#include "TextureManager.h"
#include "Game.h"

void ShooterObject::load(const LoaderParams * pParams) 
{
	if (!pParams)
	{
		return;
	}
	m_position.setX(pParams->getX());
	m_position.setY(pParams->getY());
	m_acceleration.setX(0);
	m_acceleration.setY(0);
	m_velocity.setX(0);
	m_velocity.setY(0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
}

void ShooterObject::draw()
{
	TextureManager::Instance()->draw(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, Game::Instance()->getRenderer());
}

void ShooterObject::update()
{
	m_position += m_velocity;
}

void ShooterObject::doDyingAnimation()
{
	scroll(Game::Instance()->getScrollSpeed());


	if (m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	m_dyingCounter++;
}