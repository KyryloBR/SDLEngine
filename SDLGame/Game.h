#ifndef GAME_H_
#define GAME_H_

#include "stdafx.h"
#include "TextureManager.h"
#include "Log.h"
#include "Player.h"
#include "GameStateMachine.h"

class Game
{
private:
	SDL_Window	 *		m_pWindow;
	SDL_Renderer *		m_pRenderer;
	bool				m_bRunning;
	int					m_nCurrentFrame;
	GameStateMachine *	m_pStateMachine;

	int m_windowHeight;
	int m_windowWidth;

	int m_scrollSpeed;

	int m_countLives;
	bool m_bIsLevelCompleted;

	static Game * s_pGame;
	Game();
	~Game();

	std::vector<GameObject*> m_gameObject;
public:

	bool init(const char * title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();


	bool isLevelCompleted() { return m_bIsLevelCompleted; }
	int getScrollSpeed() { return m_scrollSpeed; }

	int getPlayerLives() { return m_countLives; }
	void setPlayerLives(int _countLives) { m_countLives = _countLives; }

	bool running() { return m_bRunning; }
	void setRunning(bool _running) { m_bRunning = _running; }
	GameStateMachine * getStateMachine() { return m_pStateMachine; }
	int getWindowWidth() { return m_windowWidth; }
	int getWindowHeight() { return m_windowHeight; }
	void changeState();

	static Game * Instance();
	void release();
	SDL_Renderer * getRenderer() { return m_pRenderer; }
};

#endif // GAME_H_