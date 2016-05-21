#include "PlayState.h"
#include "Log.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "AnimationParser.h"
#include "CollisionManager.h"
#include "AnimationHandler.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::render()
{
	m_pLevel->render();
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();		
	}
}

void PlayState::update()
{
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->push_back(new PauseState());
	}
	m_pLevel->update();
	
	//if (m_pLevel->getPlayer()->getPosition()->getX() + m_pLevel->getPlayer()->getWidth() >= 635)
	//{
	//	for (int i = 0; i < m_pLevel->getLayers()->size(); ++i)
	//	{
	//		TileLayer * pTile = dynamic_cast<TileLayer*>(m_pLevel->getLayers()->at(i));
	//		if (pTile)
	//		{
	//			pTile->setColumns(20);
	//			m_pLevel->getPlayer()->setPosition(Vector2D(30, 330));
	//		}
	//	}
	//}
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->update();
	}
}

bool PlayState::onEnter()
{
	LevelParser levelParser;
	m_pLevel = levelParser.parseLevel("../assets/1.tmx");
	TextureManager::Instance()->load("Underground2", "../assets/Underground2.png", Game::Instance()->getRenderer());
	m_pLevel->getPlayer()->setEarthBorder(320);
	//AnimationHandler::Instance()->load("D:/program/SDL/SDLGame/Data/animation.xml");
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	for (int i = 0; i < m_textureIDs.size(); ++i)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureIDs[i]);
	}
	return true;
}