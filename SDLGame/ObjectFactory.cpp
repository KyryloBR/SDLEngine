#include "ObjectFactory.h"
#include "Log.h"

ObjectFactory * ObjectFactory::s_objFactory = 0;

bool ObjectFactory::registerType(std::string typeID, BaseCreator * pCreator)
{
	std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

	if (it != m_creators.end())
	{
		delete pCreator;
		return false;
	}

	m_creators[typeID] = pCreator;
	return true;
}

GameObject * ObjectFactory::create(const std::string & typeID)
{
	std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

	if (it == m_creators.end())
	{
		Log::Instance()->write("Error : could not find type.");
		return false;
	}

	BaseCreator * pCreator = it->second;
	return pCreator->createObject();
}

ObjectFactory * ObjectFactory::Instance()
{
	if (!s_objFactory)
	{
		s_objFactory = new ObjectFactory();
	}
	return s_objFactory;
}
