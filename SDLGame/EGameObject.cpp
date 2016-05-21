#include "EGameObject.h"
#include "Game.h"

EGameObject::EGameObject() : GameObject()
{
}

void EGameObject::load(const LoaderParams * pParams)
{
	if (!pParams)
		return;
	m_position.setX(pParams->getX());
	m_position.setY(pParams->getY());
	m_acceleration.setX(0);
	m_acceleration.setY(0);
	m_velocity.setX(0);
	m_velocity.setY(0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	if (m_position.getX() < 640)
	{
		m_bRendering = true;
	}
	else
	{
		m_bRendering = false;
	}
}
void EGameObject::draw()
{
	if (m_bRendering)
	TextureManager::Instance()->draw(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height,m_alpha,m_angle,
		Game::Instance()->getRenderer());

}

void EGameObject::update()
{
	if (m_position.getX() < 640)
	{
		m_bRendering = true;
	}
	m_position += m_velocity;
}

void EGameObject::clean()
{
	TextureManager::Instance()->clearFromTextureMap(m_textureID);
}
