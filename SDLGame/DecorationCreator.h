#ifndef _DECORATION_CREATOR_H_
#define _DECORATION_CREATOR_H_

#include "BaseCreator.h"
#include "Decoration.h"

class DecorationCreator : public BaseCreator
{
	GameObject * createObject() const
	{
		return new Decoration();
	}
};

#endif // _DECORATION_CREATOR_H_