#ifndef SHOOTER_OBJECT_H_
#define SHOOTER_OBJECT_H_

#include "GameObject.h"

class ShooterObject : public GameObject
{
public:
	virtual ~ShooterObject(){}
	virtual void load(const LoaderParams * pParams);
	virtual void draw();
	virtual void update();
	virtual void colision() {}
	virtual void clean() {}
	virtual std::string getType() { return "ShooterObject"; }
	ShooterObject() : GameObject() {}

protected:

	void doDyingAnimation();

	int m_bulletFiringSpeed;
	int m_bulletCount;

	int m_moveSpeed;
	
	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound;
};

#endif // SHOOTER_OBJECT_H_