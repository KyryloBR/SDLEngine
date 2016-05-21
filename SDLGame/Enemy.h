#ifndef ENEMY_H_
#define ENEMY_H_

#include "EGameObject.h"
#include "AnimationParser.h"

class Enemy : public EGameObject
{
public:
	virtual std::string getType() { return "Enemy"; }
	virtual ~Enemy() {}
	virtual void draw();
	virtual void update();
	virtual void load(const LoaderParams * pParams);
	virtual void clean() {}

	void getDamage(int nDamage) { m_nHealth -= nDamage; }

protected:
	int m_nHealth;
	int m_nDamage;
	int m_nBeginShoot;
	LoopAnimation * m_pCurrentAnimation;
};

#endif // ENEMY_H_