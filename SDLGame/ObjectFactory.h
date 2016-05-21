#ifndef OBJECTFACTORY_H_
#define OBJECTFACTORY_H_

#include "stdafx.h"
#include "BaseCreator.h"

class ObjectFactory
{
private:
	std::map<std::string, BaseCreator*> m_creators;

	ObjectFactory() {}
	~ObjectFactory() {}
	static ObjectFactory * s_objFactory;

public:
	bool registerType(std::string typeID,BaseCreator * pCreator);
	GameObject * create(const std::string & typeID);

	static ObjectFactory * Instance();
	void release() { delete s_objFactory; }
};

#endif // OBJECTFACTORY_H_