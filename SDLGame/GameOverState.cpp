#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Button.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onEnter()
{
	if (!TextureManager::Instance()->load("gameover", "../assets/GameOver.png", Game::Instance()->getRenderer()))
	{
		Log::Instance()->write("Error : game over text not loaded.");
		return false;
	}
	if (!TextureManager::Instance()->load("buttonMainMenu", "../assets/main.png", Game::Instance()->getRenderer()))
	{
		Log::Instance()->write("Error : main button not loaded.");
		return false;
	}
	
	GameObject * buttonExit = new Button(new FromGameOverToMain());
	buttonExit->load(new LoaderParams(200, 250, 200, 100, "buttonMainMenu"));
	m_gameObjects.push_back(buttonExit);

	EGameObject * gameOverText = new EGameObject();
	gameOverText->load(new LoaderParams(200, 100, 200, 100, "gameover"));
	m_gameObjects.push_back(gameOverText);
	return false;
}

bool GameOverState::onExit()
{
	Log::Instance()->write("Exit from play state");
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("buttonMainMenu");
	return true;
}