#ifndef BASECREATOR_H_
#define BASECREATOR_H_

#include "stdafx.h"
#include "GameObject.h"

class EventBase;

class BaseCreator
{
public:
	virtual GameObject * createObject() const = 0;
	virtual ~BaseCreator() {}
};

class MethodCreator
{
public:
	virtual EventBase * createMethod() const = 0;
	virtual ~MethodCreator() {}
};

#endif // BASECREATOR_H_