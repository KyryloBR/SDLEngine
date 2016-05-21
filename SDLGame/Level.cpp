#include "Level.h"
#include "ObjectLayer.h"
#include "CollisionManager.h"
#include "BulletHandler.h"
#include "AnimationHandler.h"
#include "GameStateMachine.h"
#include "GameOverState.h"
#include "Decoration.h"

Level::Level()
{
	
}

void Level::render()
{
	for (int i = 0; i < m_layers.size(); ++i)
	{
		m_layers.at(i)->render();
	}
	BulletHandler::Instance()->draw();
}

void Level::update()
{
	ObjectLayer * pObjects;
	for (int i = 0; i < m_layers.size(); ++i)
	{
		if (m_pPlayer->getPosition()->getX() + m_pPlayer->getWidth() > 635)
		{
			TileLayer * pTile = dynamic_cast<TileLayer*>(m_layers[i]);
			if (pTile && pTile->getNumColumns() + pTile->getColumnIncrement() < pTile->getTileIDs().at(0).size())
			{
 				pTile->setColumns(20);
				m_pPlayer->setPosition(Vector2D(10, 330));
				BulletHandler::Instance()->clearAll();
				scrollObjects();
			}
			else
			{
				m_pPlayer->setVelocity(Vector2D(0.0, 0.0));
			}
		}
		m_layers[i]->update();
		pObjects = dynamic_cast<ObjectLayer*>(m_layers[i]);
		if (pObjects)
		{
			CollisionManager::Instance()->checkEnemyPlayerBulletCollision(BulletHandler::Instance()->getBulletPlayer(), pObjects->getObjects());
		}
	}
	CollisionManager::Instance()->checkPlayerEnemyBulletCollision(m_pPlayer, BulletHandler::Instance()->getBulletEnemy());
	BulletHandler::Instance()->update();
	if (m_pPlayer->isDead())
	{
		Game::Instance()->getStateMachine()->changeState(new GameOverState());
	}
}

void Level::scrollObjects()
{
	for (int i = 0; i < m_layers.size(); ++i)
	{
		ObjectLayer * pObjects = dynamic_cast<ObjectLayer*>(m_layers[i]);
		if (pObjects)
		{
			for (int i = 0; i < pObjects->getObjects()->size(); ++i)
			{
				if (pObjects->getObjects()->at(i)->getType() != std::string("Player") && pObjects->getObjects()->at(i)->getPosition()->getX() > Game::Instance()->getWindowWidth())
				{
					pObjects->getObjects()->at(i)->setPosition(Vector2D(pObjects->getObjects()->at(i)->getPosition()->getX() - Game::Instance()->getWindowWidth(), pObjects->getObjects()->at(i)->getPosition()->getY()));
				}
			}
		}
	}
}