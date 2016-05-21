#ifndef OBJECTLAYER_H_
#define OBJECTLAYER_H_

#include "Layer.h"
#include "stdafx.h"
#include "Enemy.h"
#include "Decoration.h"

class ObjectLayer : public Layer
{
public:
	virtual void update();
	virtual void render();

	std::vector<GameObject*> * getObjects()
	{
		return &m_objects;
	}

private:
	std::vector<GameObject*> m_objects;
};

#endif // OBJECTLAYER_H_