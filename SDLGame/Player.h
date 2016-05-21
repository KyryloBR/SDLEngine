#ifndef PLAYER_H_
#define PLAYER_H_
#define _ENDURANCE_ON_HIT_ 25
#define _ENDURANCE_ROLLBACK_ 10

#include "Weapon.h"

class LoopAnimation;

class Player : public EGameObject
{
private:
	void handleInput();
	void handleMovement();

	void ressurect();
	void handleAnimation();

	int m_nEarthBorder;
	int m_nHealth;
	int m_nDamage;
	int m_nEndurance;

	bool m_bUp;
	bool m_bForward;
	bool m_bDown;
	bool m_bBack;
	bool m_bAttack;

	Vector2D m_PositionBeforeJump;

	std::string m_button;
	int m_nCountBullet;
	//std::map<std::string, LoopAnimation*> m_animations;
	LoopAnimation * m_pCurrentAnimation;

public:

	Player();

	virtual void load(const LoaderParams * pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual std::string getType() { return "Player"; }
	Vector2D * getVelocity() { return &m_velocity; }

	int getDamage(int nDamage = 0) { 
		if (nDamage > 0) 
		{ 
			m_nHealth -= nDamage; 
		}
		else
		{
			return m_nDamage;
		}
	}

	int getEndurance() { return m_nEndurance; }

	void setForwardWalk(bool _walking) { m_bForward = _walking; }
	void setDown(bool _siting) { m_bDown = _siting; }
	void setBackWalk(bool _walking) { m_bBack = _walking; }
	void setEarthBorder(int _border) { m_nEarthBorder = _border; }

	bool isForwardWalk() { return m_bForward; }
	bool isDown() { return m_bDown; }
	bool isBackWalk() { return m_bBack; }
	bool isAttack() { return m_bAttack; }

	void setVelocity(Vector2D _velocity)
	{
		m_velocity = _velocity;
	}
	void setDying(bool _dying)
	{
		m_bDying = _dying;
	}
	
	void setAcceleration(Vector2D _acceleration)
	{
		m_acceleration = _acceleration;
	}
};
#endif // PLAYER_H_