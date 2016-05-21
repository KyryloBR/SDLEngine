#include "CollisionManager.h"
#include "Colision.h"
#include "Enemy.h"
#include "ObjectLayer.h"

CollisionManager * CollisionManager::s_pInstance = 0;

void CollisionManager::checkPlayerTileCollision(Player * pPlayer, std::vector<Layer*> & pLayers)
{
	for (std::vector<Layer*>::iterator it = pLayers.begin(); it != pLayers.end(); ++it)
	{
		TileLayer * pTileLayer = dynamic_cast<TileLayer*>(*it);
		if (!pTileLayer)
		{
			continue;
		}
		std::vector<std::vector<int>> Tiles = pTileLayer->getTileIDs();
		CheckAreaPlayer(pPlayer, Tiles, pTileLayer->getTileSize());
	}
}

void CollisionManager::CheckUp(Player * pPlayer, std::vector<std::vector<int>> & Tiles, int tileSize)
{
	int tileRow, tileColumn;
	tileColumn = pPlayer->getPosition()->getX() / tileSize;
	tileRow = pPlayer->getPosition()->getY() / tileSize;

	if (Tiles[tileRow][tileColumn] != 0 || Tiles[tileRow][tileColumn + 1] != 0 || Tiles[tileRow][tileColumn + 2] != 0)
	{
		pPlayer->setVelocity(Vector2D(0.0, 20.0));
	}
}

void CollisionManager::CheckForward(Player * pPlayer, std::vector<std::vector<int>> & Tiles, int tileSize)
{
	int tileRow, tileColumn;
	tileColumn = (pPlayer->getPosition()->getX() + pPlayer->getWidth()) / tileSize;
	tileRow = pPlayer->getPosition()->getY() / tileSize;

	if (Tiles[tileRow][tileColumn] != 0 || Tiles[tileRow + 1][tileColumn] != 0 || Tiles[tileRow + 2][tileColumn] != 0)
	{
		pPlayer->setForwardWalk(false);
		pPlayer->setVelocity(Vector2D(0.0, 0.0));
	}
	else
	{
		pPlayer->setForwardWalk(true);
	}
}

void CollisionManager::CheckDown(Player * pPlayer, std::vector<std::vector<int>> & Tiles, int tileSize)
{
	int tileColumn, tileRow, tileID = 0;
	tileColumn = (pPlayer->getPosition()->getX() + (pPlayer->getWidth() / 2)) / tileSize;
	tileRow = (pPlayer->getPosition()->getY() + pPlayer->getHeight()) / tileSize;

	if (Tiles[tileRow][tileColumn] == 0 && Tiles[tileRow][tileColumn - 1] == 0 && Tiles[tileRow][tileColumn + 1] == 0)
	{
		pPlayer->setVelocity(Vector2D(0.0, 20.0));
		pPlayer->setDown(false);
	}
	else
	{
		pPlayer->setDown(true);
	}
}

void CollisionManager::CheckBack(Player * pPlayer, std::vector<std::vector<int>> & Tiles, int tileSize)
{
	int tileRow, tileColumn;
	tileColumn = (pPlayer->getPosition()->getX() + tileSize) / tileSize;
	tileRow = pPlayer->getPosition()->getY() / tileSize;
	
	if (Tiles[tileRow][tileColumn] != 0 || Tiles[tileRow + 1][tileColumn])
	{
		pPlayer->setBackWalk(false);
		pPlayer->setVelocity(Vector2D(0.0, 0.0));
	}
	else
	{
		pPlayer->setBackWalk(true);
	}
}

void CollisionManager::CheckAreaPlayer(Player * pPlayer, std::vector<std::vector<int>> & Tiles, int tileSize)
{
	CheckUp(pPlayer, Tiles, tileSize);
	CheckForward(pPlayer, Tiles, tileSize);
	CheckDown(pPlayer, Tiles, tileSize);
	CheckBack(pPlayer, Tiles, tileSize);
}

bool CollisionManager::checkPlayerEnemyBulletCollision(Player * pPlayer, AmmoObject * pAmmo)
{
	SDL_Rect * rectPlayer = new SDL_Rect();
	rectPlayer->h = pPlayer->getHeight();
	rectPlayer->w = pPlayer->getWidth();
	rectPlayer->x = pPlayer->getPosition()->getX();
	rectPlayer->y = pPlayer->getPosition()->getY();

	SDL_Rect * rectAmmo = new SDL_Rect();	
	rectAmmo->h = pAmmo->getHeight();
	rectAmmo->w = pAmmo->getWidth();
	rectAmmo->x = pAmmo->getPosition()->getX();
	rectAmmo->y = pAmmo->getPosition()->getY();
	if (Colision::RectRect(rectAmmo, rectPlayer))
	{
		pAmmo->setHit(true);
		pPlayer->getDamage(pAmmo->getDamage());
	}
	return Colision::RectRect(rectAmmo, rectPlayer) ? true : false;
}

bool CollisionManager::checkEnemyPlayerBulletCollision(AmmoObject * pAmmo, std::vector<GameObject*> * pObjects)
{
	for (std::vector<GameObject*>::iterator it = pObjects->begin(); it != pObjects->end(); ++it)
	{
		SDL_Rect * rectAmmo = new SDL_Rect();
		rectAmmo->h = pAmmo->getHeight();
		rectAmmo->w = pAmmo->getWidth();
		rectAmmo->x = pAmmo->getPosition()->getX();
		rectAmmo->y = pAmmo->getPosition()->getY();

		SDL_Rect * rectObj = new SDL_Rect();
		rectObj->h = (*it)->getHeight();
		rectObj->w = (*it)->getWidth();
		rectObj->x = (*it)->getPosition()->getX();
		rectObj->y = (*it)->getPosition()->getY();

		if (Colision::RectRect(rectAmmo, rectObj))
		{
			pAmmo->setHit(true);
			return true;
		}
	}
	return false;
}

void CollisionManager::checkPlayerEnemyBulletCollision(Player * pPlayer, std::vector<AmmoObject*>& Bullets)
{
	for (std::vector<AmmoObject*>::iterator pAmmo = Bullets.begin(); pAmmo != Bullets.end(); ++pAmmo)
	{
		SDL_Rect * rectPlayer = new SDL_Rect();
		rectPlayer->h = pPlayer->getHeight();
		rectPlayer->w = pPlayer->getWidth();
		rectPlayer->x = pPlayer->getPosition()->getX();
		rectPlayer->y = pPlayer->getPosition()->getY();

		SDL_Rect * rectAmmo = new SDL_Rect();
		rectAmmo->h = (*pAmmo)->getHeight();
		rectAmmo->w = (*pAmmo)->getWidth();
		rectAmmo->x = (*pAmmo)->getPosition()->getX();
		rectAmmo->y = (*pAmmo)->getPosition()->getY();
		if (Colision::RectRect(rectAmmo, rectPlayer))
		{
			(*pAmmo)->setHit(true);
			pPlayer->getDamage((*pAmmo)->getDamage());
		}
	}
}

void CollisionManager::checkEnemyPlayerBulletCollision(std::vector<AmmoObject*> & Bullets, std::vector<GameObject*> * pObjects)
{
	for (std::vector<GameObject*>::iterator it = pObjects->begin(); it != pObjects->end(); ++it)
	{
		for (std::vector<AmmoObject*>::iterator pAmmo = Bullets.begin(); pAmmo != Bullets.end(); ++pAmmo)
		{
			SDL_Rect * rectAmmo = new SDL_Rect();
			rectAmmo->h = (*pAmmo)->getHeight();
			rectAmmo->w = (*pAmmo)->getWidth();
			rectAmmo->x = (*pAmmo)->getPosition()->getX();
			rectAmmo->y = (*pAmmo)->getPosition()->getY();

			SDL_Rect * rectObj = new SDL_Rect();
			rectObj->h = (*it)->getHeight();
			rectObj->w = (*it)->getWidth();
			rectObj->x = (*it)->getPosition()->getX();
			rectObj->y = (*it)->getPosition()->getY();

			if (Colision::RectRect(rectAmmo, rectObj))
			{
				(*pAmmo)->setHit(true);
				Enemy * pEnemy = dynamic_cast<Enemy*>(*it);
				if (pEnemy)
				{
					pEnemy->getDamage((*pAmmo)->getDamage());
				}
			}
		}
	}
}

void CollisionManager::checkPlayerEnemyCollision()
{
	for (std::vector<Layer*>::iterator layer = m_pLevel->getLayers()->begin(); layer != m_pLevel->getLayers()->end(); ++layer)
	{
		ObjectLayer * pObjects = dynamic_cast<ObjectLayer*>(*layer);
		if (pObjects)
		{
			Player * pPlayer = m_pLevel->getPlayer();
			for (std::vector<GameObject*>::iterator it = pObjects->getObjects()->begin(); it != pObjects->getObjects()->end(); ++it)
			{
				if ((*it)->isRendering() && !(*it)->isDead())
				{
					SDL_Rect * rectPlayer = new SDL_Rect();
					rectPlayer->h = pPlayer->getHeight();
					rectPlayer->w = pPlayer->getWidth();
					rectPlayer->x = pPlayer->getPosition()->getX();
					rectPlayer->y = pPlayer->getPosition()->getY();

					SDL_Rect * rectObj = new SDL_Rect();
					rectObj->h = (*it)->getHeight();
					rectObj->w = (*it)->getWidth();
					rectObj->x = (*it)->getPosition()->getX();
					rectObj->y = (*it)->getPosition()->getY();

					if (Colision::RectRect(rectPlayer, rectObj))
					{
						Enemy * pEnemy = dynamic_cast<Enemy*>(*it);
						if (pPlayer->isAttack() && pEnemy)
						{
							pEnemy->getDamage(pPlayer->getDamage());
						}
						else if (pEnemy)
						{
							pPlayer->setVelocity(Vector2D(0, pPlayer->getVelocity()->getY()));
						}
					}
				}
			}
		}
	}
}

bool CollisionManager::checkMeleeWeaponWithEnemy(Melee * pWeapon)
{
	for (std::vector<GameObject*>::iterator it = m_pObjectLayer->getObjects()->begin(); it != m_pObjectLayer->getObjects()->end(); ++it)
	{
		if ((*it)->getType() == std::string("Enemy"))
		{
			SDL_Rect * rectObj = new SDL_Rect();
			rectObj->h = (*it)->getHeight();
			rectObj->w = (*it)->getWidth();
			rectObj->x = (*it)->getPosition()->getX();
			rectObj->y = (*it)->getPosition()->getY();

			SDL_Rect * rectWeapon = new SDL_Rect();
			rectWeapon->h = pWeapon->getHeight();
			rectWeapon->w = pWeapon->getWidth();
			rectWeapon->x = pWeapon->getPosition()->getX();
			rectWeapon->y = pWeapon->getPosition()->getY();

			if (Colision::RectRect(rectObj, rectWeapon))
			{
				return true;
			}
		}
	}
	return false;
}