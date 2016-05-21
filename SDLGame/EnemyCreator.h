#ifndef _ENEMY_CREATOR_H_
#define _ENEMY_CREATOR_H_

#include "BaseCreator.h"
#include "Enemy.h"

class EnemyCreator : public BaseCreator
{
	GameObject * createObject() const
	{
		return new Enemy();
	}
};

#endif // _ENEMY_CREATOR_H_