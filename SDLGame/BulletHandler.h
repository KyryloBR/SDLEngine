#ifndef BULLET_HANDLER_H_
#define BULLET_HANDLER_H_

#include "Vector2D.h"
#include "AmmoObject.h"

class BulletHandler 
{
public:
	static BulletHandler * Instance() 
	{
		if (!s_pInstance)
			s_pInstance = new BulletHandler();
		return s_pInstance; 
	}
	void addPlayerBullet(int x, int y, int width, int height, const std::string textureID, Vector2D velocity);
	void addEnemyBullet(int x, int y, int width, int height, const std::string textureID, Vector2D velocity);
	void draw();
	void update();
	void clearAll();

	std::vector<AmmoObject*>& getBulletPlayer() { return m_pBulletsPlayer; }
	std::vector<AmmoObject*>& getBulletEnemy() { return m_pBulletsEnemy; }

private:
	static BulletHandler * s_pInstance;
	BulletHandler() {} 
	~BulletHandler() {}

	std::vector<AmmoObject*> m_pBulletsPlayer;
	std::vector<AmmoObject*> m_pBulletsEnemy;
};

#endif // BULLET_HANDLER_H_