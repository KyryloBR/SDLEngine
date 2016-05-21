#include "ListView.h"

void ListView::update()
{
	m_Objects[m_nCurrentIndex]->update();
}

void ListView::draw()
{
	if (!m_Objects.empty())
	{
		m_Objects[m_nCurrentIndex]->draw();
	}
}

void ListView::load(LoaderParams * pParams)
{
	m_height = pParams->getHeight();
	m_width = pParams->getWidth();
	m_position.setX(pParams->getX());
	m_position.setY(pParams->getY());
	m_velocity.setX(0);
	m_velocity.setY(0);
	m_acceleration.setX(0);
	m_acceleration.setY(0);
	m_textureID = pParams->getTextureID();
}

void ListView::clean()
{
	for (std::vector<GameObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it)
	{
		(*it)->clean();
	}
	m_Objects.clear();
}

void ListView::push_back(GameObject * pObj)
{
	if (pObj)
	{
		pObj->setWidth(this->m_width - 40);
		pObj->setHeight(this->m_height - 40);
		pObj->setPosition(Vector2D(this->m_position.getX() - 20, this->m_position.getY() - 20));
		pObj->setRendeering(false);
		m_Objects.push_back(pObj);
	}
	m_Objects[m_nCurrentIndex]->setRendeering(true);
}

void ListView::pop_back()
{
	if (!m_Objects.empty())
	{
		m_Objects.pop_back();
	}
}

RESULT_LIST_VIEW ListView::increase()
{
	if (m_Objects.size() - 1 < m_nCurrentIndex)
	{
		m_nCurrentIndex++;
		return LV_OK;
	}
	else
	{
		return LV_INCREASE_INVALID;
	}
}

RESULT_LIST_VIEW ListView::decrease()
{
	if (m_nCurrentIndex > 0)
	{
		m_nCurrentIndex--;
		return LV_OK;
	}
	else
	{
		return LV_DECREASE_INVALID;
	}
}

