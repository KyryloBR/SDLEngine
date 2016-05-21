#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include "Player.h"
#include "TileLayer.h"
#include "AmmoObject.h"
#include "ObjectLayer.h"
#include "Level.h"
#include "Melee.h"

class CollisionManager
{
private:
	CollisionManager() {}
	~CollisionManager() {}
	static CollisionManager * s_pInstance;
	Level * m_pLevel;
	ObjectLayer * m_pObjectLayer;

	void CheckAreaPlayer(Player * pPlayer, std::vector<std::vector<int>> & Tiles, int tileSize);

	void CheckUp(Player * pPlayer, std::vector<std::vector<int>> & Tiles,int tileSize);
	void CheckForward(Player * pPlayer, std::vector<std::vector<int>> & Tiles, int tileSize);
	void CheckDown(Player * pPlayer, std::vector<std::vector<int>> & Tiles, int tileSize);
	void CheckBack(Player * pPlayer, std::vector<std::vector<int>> & Tiles, int tileSize);

public:
	void checkPlayerEnemyCollision();

	// Player
	bool checkPlayerEnemyBulletCollision(Player * pPlayer, AmmoObject * pAmmo);
	void checkPlayerEnemyBulletCollision(Player * pPlayer, std::vector<AmmoObject*>& Bullets);

	// Enemy
	bool checkEnemyPlayerBulletCollision(AmmoObject * pAmmo, std::vector<GameObject*> * pObjects);
	void checkEnemyPlayerBulletCollision(std::vector<AmmoObject*>& Bullets, std::vector<GameObject*> * pObjects);
	
	void checkPlayerTileCollision(Player * pPlayer, std::vector<Layer*> & pLayers);

	bool checkMeleeWeaponWithEnemy(Melee * pWeapon);

	void setLevel(Level * pLevel) 
	{ 
		m_pLevel = pLevel;
		for (std::vector<Layer*>::iterator it = m_pLevel->getLayers()->begin(); it != m_pLevel->getLayers()->end(); ++it)
		{
			if (dynamic_cast<ObjectLayer*>(*it))
			{
				m_pObjectLayer = dynamic_cast<ObjectLayer*>(*it);
			}
		}
	}

	static CollisionManager * Instance() 
	{
		if (!s_pInstance)
		{
			s_pInstance = new CollisionManager();
		}
		return s_pInstance; 
	}
};

#endif // COLLISION_MANAGER_H_