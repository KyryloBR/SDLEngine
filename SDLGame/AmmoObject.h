#ifndef _AMMO_OBJECT_H_
#define _AMMO_OBJECT_H_

#include "EGameObject.h"

class AmmoObject : public EGameObject
{
public:
	AmmoObject();
	virtual void load(const LoaderParams * pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual std::string getType() { return "Ammo"; }

	void setDamage(int nDamage) { m_nDamage = nDamage; }
	void setShooting(bool bShooting) { m_bShooting = bShooting; }
	void setHit(bool bHit) { m_bHit = bHit; }
	void setVelocity(Vector2D velocity) { m_velocity = velocity; }

	int getDamage() { return m_nDamage; }
	bool isShooting() { return m_bShooting; }
	bool isHit() { return m_bHit; }

private:
	int m_nDamage;

	bool m_bShooting;
	bool m_bHit;
};

#endif // _AMMO_OBJECT_H_