#include "ObjectLayer.h"

void ObjectLayer::update()
{
	for (std::vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
	{
		if ((*it)->getPosition()->getX() < 640)
		{
			(*it)->update();
		}
	}
}

void ObjectLayer::render()
{
	for (int i = 0; i < m_objects.size(); ++i)
	{
		m_objects[i]->draw();
	}
}