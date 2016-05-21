#ifndef _MELEE_H_
#define _MELEE_H_

#include "Weapon.h"

class Melee : public Weapon
{
public:
	Melee() : Weapon() {}
	virtual void load(const LoaderParams * pParams);
	virtual void update();
	virtual void draw();
	virtual std::string getType() { return "Melee"; }
	virtual void attack();
};

#endif // _MELEE_H_