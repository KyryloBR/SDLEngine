#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "GameState.h"
#include "stdafx.h"
#include "GameObject.h"
#include "EventBase.h"
#include "Game.h"
#include "MenuState.h"
#include "BaseCreator.h"
#include "MoveAnimation.h"

class PauseState : public GameState
{
private:
	std::vector<GameObject*> m_gameObjects;
	static const std::string s_pauseID;
	MoveAnimation * m_animation;

public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }
};

class ResumeGame : public EventBase
{
public:
	ResumeGame() : EventBase()
	{
		s_eventID = "RESUME EVENT";
	}
	virtual void operator()()
	{
		Game::Instance()->getStateMachine()->pop_state();
	}
};

class FromPauseToMain : public EventBase
{
public:
	FromPauseToMain() : EventBase()
	{
		s_eventID = "PAUSE TO MAIN";
	}
	virtual void operator()()
	{
		Game::Instance()->getStateMachine()->changeState(new MenuState());
	}
};

#endif // PAUSESTATE_H_