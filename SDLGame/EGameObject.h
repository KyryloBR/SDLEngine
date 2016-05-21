#ifndef EGAMEOBJECT_H_
#define EGAMEOBJECT_H_
#include "stdafx.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "LoopAnimation.h"

class EGameObject : public GameObject
{
protected:
	std::map<std::string, LoopAnimation*> m_animations;

public:
	EGameObject();

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams * pParams);
	virtual std::string getType() { return "EGameObject"; }
};


#endif // EGAMEOBJECT_H_