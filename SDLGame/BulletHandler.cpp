#include "BulletHandler.h"
#include "PlayerBullet.h"
#include "Game.h"

BulletHandler * BulletHandler::s_pInstance = 0;

void BulletHandler::addPlayerBullet(int x, int y, int width, int height, const std::string textureID, Vector2D velocity)
{
	AmmoObject * pAmmo = new AmmoObject();
	pAmmo->load(new LoaderParams(x, y, width, height, textureID));
	pAmmo->setVelocity(velocity);

	m_pBulletsPlayer.push_back(pAmmo);
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height, const std::string textureID, Vector2D velocity)
{
	AmmoObject * pAmmo = new AmmoObject();
	pAmmo->load(new LoaderParams(x, y, width, height, textureID));
	pAmmo->setVelocity(velocity);

	m_pBulletsEnemy.push_back(pAmmo);
}

void BulletHandler::draw()
{
	for (int i = 0; i < m_pBulletsEnemy.size(); ++i)
	{
		m_pBulletsEnemy.at(i)->draw();
	}
	for (int i = 0; i < m_pBulletsPlayer.size(); ++i)
	{
		m_pBulletsPlayer.at(i)->draw();
	}
}

void BulletHandler::update()
{
	for (std::vector<AmmoObject*>::iterator it = m_pBulletsPlayer.begin(); it != m_pBulletsPlayer.end();)
	{
		if ((*it)->getPosition()->getX() < 0 || (*it)->getPosition()->getX() > Game::Instance()->getWindowWidth() || (*it)->isHit())
		{
			it = m_pBulletsPlayer.erase(it);
		}
		else
		{
			(*it)->update();
			++it;
		}
	}

	for (std::vector<AmmoObject*>::iterator it = m_pBulletsEnemy.begin(); it != m_pBulletsEnemy.end();)
	{
		if ((*it)->getPosition()->getX() < 0 || (*it)->getPosition()->getX() > Game::Instance()->getWindowWidth() ||
			(*it)->getPosition()->getY() < 0 || (*it)->getPosition()->getY() > Game::Instance()->getWindowHeight() || (*it)->isHit())
		{
			it = m_pBulletsEnemy.erase(it);
		}
		else
		{
			(*it)->update();
			++it;
		}
	}
}

void BulletHandler::clearAll()
{
	if (!m_pBulletsEnemy.empty())
	{
		m_pBulletsEnemy.clear();
	}
	if (!m_pBulletsPlayer.empty())
	{
		m_pBulletsPlayer.clear();
	}
}