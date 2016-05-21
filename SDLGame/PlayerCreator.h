#ifndef PLAYERCREATOR_H_
#define PLAYERCREATOR_H_

#include "BaseCreator.h"
#include "Player.h"

class PlayerCreator : public BaseCreator
{
	GameObject * createObject() const
	{
		return new Player();
	}
};

#endif // PLAYERCREATOR_H_