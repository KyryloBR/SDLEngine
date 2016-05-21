#include "Game.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PlayerCreator.h"
#include "ObjectFactory.h"
#include "SequenceState.h"
#include "GameOverState.h"
#include "EnemyCreator.h"
#include "DecorationCreator.h"
#include "LogoState.h"

Game * Game::s_pGame = 0;

Game::Game()
{
	m_nCurrentFrame = 0;
	m_windowWidth = 640;
	m_windowHeight = 480;
	m_bIsLevelCompleted = true;
}
Game::~Game()
{
	clean();
}

bool Game::init(const char * title, int xpos, int ypos, int width, int height, int flags)
{
	m_windowHeight = height;
	m_windowWidth = width;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		Log::Instance()->write("Info : SDL instruments were initialized .");

		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			Log::Instance()->write("Info : Window created.");

			if (m_pRenderer != 0)
			{
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
				ObjectFactory::Instance()->registerType("Player", new PlayerCreator());
				ObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
				ObjectFactory::Instance()->registerType("Decoration", new DecorationCreator());
				m_pStateMachine = new GameStateMachine();
				m_pStateMachine->push_back(new MenuState());
				SequenceState * m_pSequence = new SequenceState();
				m_pSequence->push_state(3000, new LogoState("Logo1", "../assets/nd.png",300,100));
				m_pSequence->push_state(3000, new LogoState("Logo", "../assets/logo.bmp",100,200));
				m_pStateMachine->push_back(m_pSequence);
				InputHandler::Instance()->initialiseJoystick();
			}
			else
			{
				Log::Instance()->write("Error : Renderer not created and was initialized.");
				return false;
			}
		}
		else
		{
			Log::Instance()->write("Error : Window was not created.");
			return false;
		}
	}
	else
	{
		Log::Instance()->write("Error : SDL instruments were not initialized .");
		return false;
	}
	m_bRunning = true;
	return true;
}
void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	//TextureManager::Instance()->draw("level", 0, 0, m_windowWidth, m_windowHeight, m_pRenderer);
	
	m_pStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}
void Game::handleEvents()
{
	InputHandler::Instance()->update();
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pStateMachine->changeState(new PlayState());
	}
}

void Game::changeState()
{
	m_pStateMachine->changeState(new PlayState());
}

void Game::update()
{
	m_pStateMachine->update();
}


void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TextureManager::Instance()->release();
	Log::Instance()->release();
	InputHandler::Instance()->release();
	SDL_Quit();
}

Game* Game::Instance()
{
	if (!s_pGame)
	{
		s_pGame = new Game();
	}
	return s_pGame;
}
void Game::release()
{
	if (s_pGame)
		delete s_pGame;
}