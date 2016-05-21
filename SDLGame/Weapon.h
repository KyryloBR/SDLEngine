#ifndef _WEAPON_H_
#define _WEAPON_H_
#define _DAMAGE_ 30

#include "EGameObject.h"

class Weapon : public EGameObject
{
private:
	float m_nDamage;
	LoopAnimation * m_pCurrentAnimation;

public:
	Weapon() : EGameObject(), m_nDamage(30) {}
	virtual void load(const LoaderParams * pParams);
	virtual void draw();
	virtual void clean();
	virtual void update();
	virtual std::string getType() { return "Weapon"; }
	int getDamage() { return m_nDamage; }
	virtual void attack() = 0;
	Vector2D * getVelocity() { return &m_velocity; }
	void setVelocity(Vector2D velocity) { m_velocity = velocity; }
	
};
#endif // _WEAPON_H_