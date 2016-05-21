#include "PauseState.h"
#include "Game.h"
#include "MenuState.h"
#include "Button.h"
#include "InputHandler.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->update();
	}
}
void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if (!TextureManager::Instance()->load("resume", "../assets/resume.png", Game::Instance()->getRenderer()))
	{
		Log::Instance()->write("Error : Button resume not loaded.");
		return false;
	}
	if (!TextureManager::Instance()->load("main", "../assets/main.png", Game::Instance()->getRenderer()))
	{
		Log::Instance()->write("Error : Button main not loaded.");
		return false;
	}
	if (!TextureManager::Instance()->load("exit", "../assets/btnExit.png", Game::Instance()->getRenderer()))
	{
		Log::Instance()->write("Error : Button exit not loaded.");
		return false;
	}

	GameObject * btnResume = new Button(new ResumeGame());
	btnResume->load(new LoaderParams(200, 100, 200, 100, "resume"));

	GameObject * btnMain = new Button(new FromPauseToMain());
	btnResume->load(new LoaderParams(200, 200, 200, 100, "main"));

	GameObject * btnExit = new Button(new ToExit());
	btnExit->load(new LoaderParams(200, 300, 200, 100, "exit"));

	m_gameObjects.push_back(btnResume);
	m_gameObjects.push_back(btnMain);
	m_gameObjects.push_back(btnExit);
	
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->clean();
	}
	TextureManager::Instance()->clearFromTextureMap("exit");
	TextureManager::Instance()->clearFromTextureMap("main");
	TextureManager::Instance()->clearFromTextureMap("resume");

	return true;
}