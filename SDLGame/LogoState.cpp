#include "LogoState.h"
#include "Game.h"

LogoState::LogoState(const std::string & logoID, const std::string & filename, int width, int height) : GameState(), m_width(width), m_height(height)
{
	TextureManager::Instance()->load(logoID, filename, Game::Instance()->getRenderer());
	m_logoID = logoID;
}

bool LogoState::onEnter()
{
	m_logo = new EGameObject();
	m_logo->load(new LoaderParams(320 - (m_width / 2), 240 - (m_height/2), m_width, m_height, m_logoID));
	return true;
}

bool LogoState::onExit()
{
	if (m_logo)
	{
		TextureManager::Instance()->clearFromTextureMap(m_logoID);
		return true;
	}
	return false;
}

void LogoState::update()
{
	m_logo->update();
}

void LogoState::render()
{
	m_logo->draw();
}