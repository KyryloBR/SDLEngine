#include "Enemy.h"
#include "Game.h"
#include "BulletHandler.h"
#include <chrono>
#include <time.h>

void Enemy::draw()
{
	if (!m_bDead && m_bRendering)
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

void Enemy::update()
{
	if (!m_bDead)
	{
		//int durationTime = SDL_GetTicks() - m_nBeginShoot;
		//int moreThen = 1000 + rand() % 2000;
		//if (durationTime >= moreThen)
		//{
		//	BulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + (m_height / 2), 40, 10, "EnemyBullet", Vector2D(-20, 0));
		//	m_nBeginShoot = SDL_GetTicks();
		//}
		if (m_nHealth <= 0)
		{
			m_bDead = true;
		}
		m_position += m_velocity;
		if (m_position.getX() < 640)
		{
			m_bRendering = true;
		}
		else
		{
			m_bRendering = false;
		}
	}
}


void Enemy::load(const LoaderParams * pParams)
{
	EGameObject::load(pParams);
	m_nHealth = 100;
	m_bDead = false;
	m_nFlip = SDL_FLIP_HORIZONTAL;
	AnimationParser parser;
	parser.parseAnimation(m_animations, "../Data/animations.xml", getType());
	m_animations["WalkingEnemy"]->setLoopAlways(true);
	m_pCurrentAnimation = m_animations["WalkingEnemy"];
	m_pCurrentAnimation->play();
	m_nBeginShoot = SDL_GetTicks();
}