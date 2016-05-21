#ifndef GAMEOVERSTATE_H_
#define GAMEOVERSTATE_H_

#include "GameState.h"
#include "stdafx.h"
#include "GameObject.h"
#include "BaseCreator.h"
#include "Game.h"
#include "EventBase.h"
#include "MenuState.h"

class GameOverState : public GameState
{
private:
	static const std::string s_gameOverID;
	std::vector<GameObject*> m_gameObjects;

public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; }
};

class FromGameOverToMain : public EventBase
{
public:
	FromGameOverToMain() : EventBase()
	{
		s_eventID = "EXIT TO MAIN";
	}
	virtual void operator()()
	{
		Game::Instance()->getStateMachine()->changeState(new MenuState());
	}
};

#endif // GAMEOVERSTATE_H_