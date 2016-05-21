#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::draw(SDL_Renderer * pRenderer)
{
	TextureManager::Instance()->drawFrame(m_textureId, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, pRenderer);
}

void GameObject::update()
{
	m_x += 1;
}

void GameObject::clear()
{

}