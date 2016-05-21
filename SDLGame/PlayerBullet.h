#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

#include "ShooterObject.h"

class PlayerBullet : public ShooterObject
{
public:
	PlayerBullet() : ShooterObject() {}
	virtual ~PlayerBullet() {}
	virtual std::string getType() { return "Player Bullet"; }
	virtual void load(const LoaderParams * pParams, Vector2D * heading)
	{
		ShooterObject::load(pParams);
		m_heading = heading;
	}
	virtual void draw()
	{
		ShooterObject::draw();
	}
	virtual void colision()
	{
		m_bDead = true;
	}
	virtual void update()
	{
		m_velocity.setX(m_heading->getX());
		m_velocity.setY(m_heading->getY());

		ShooterObject::update();
	}
	virtual void clean()
	{
		ShooterObject::clean();
	}

private:
	Vector2D * m_heading;

};


class EnemyBullet : public PlayerBullet
{
public:
	EnemyBullet() : PlayerBullet() {}
	virtual ~EnemyBullet() {}
	virtual std::string getType() { return "Enemy Bullet"; }
};

#endif //__PLAYER_BULLET_H__