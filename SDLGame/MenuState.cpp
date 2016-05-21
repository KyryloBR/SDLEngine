#include "MenuState.h"
#include "Log.h"
#include "TextureManager.h"
#include "Game.h"
#include "Button.h"
#include "PlayState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}
}

void MenuState::update()
{
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			m_gameObjects[i]->update();
		}
}

bool MenuState::onEnter()
{

//D: / program / SDL / SDLGame /
	if (!TextureManager::Instance()->load("playbutton", "../assets/btnPlay.png", Game::Instance()->getRenderer()))
	{
		Log::Instance()->write("Error : Don`t load playbutton texture.");
		return false;
	}
	if (!TextureManager::Instance()->load("exitbutton", "../assets/btnExit.png", Game::Instance()->getRenderer()))
	{
		Log::Instance()->write("Error : Don`t load exitbutton texture.");
		return false;
	}
	GameObject * buttonPlay = new Button(new FromMenuToPlay());
	buttonPlay->load(new LoaderParams(200, 100, 200, 100, "playbutton"));
	GameObject * buttonExit = new Button(new ToExit());
	buttonExit->load(new LoaderParams(200, 200, 200, 100, "exitbutton"));


	m_gameObjects.push_back(buttonPlay);
	m_gameObjects.push_back(buttonExit);
	return true;
}

bool MenuState::onExit()
{
	Log::Instance()->write("Exit Menu state");
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("playbutton");
	TextureManager::Instance()->clearFromTextureMap("exitbutton");
	return true;
}