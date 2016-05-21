#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "GameObject.h"
#include "GameState.h"
#include "EventBase.h"
#include "Game.h"
#include "PlayState.h"
#include "BaseCreator.h"
#include "NumberAnimation.h"

class MenuState : public GameState
{
private :
	static const std::string s_menuID;
	std::vector<GameObject*> m_gameObjects;
	NumberAnimation * m_numberAnimation;
public:
	MenuState() {}
	virtual void render();
	virtual void update();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }
};

class FromMenuToPlay : public EventBase
{
public:
	FromMenuToPlay() : EventBase()
	{
		s_eventID = "MENU TO PLAY EVENT";
	}
	virtual void operator()()
	{
		Log::Instance()->write("Info : Play button clicked!");
		Game::Instance()->getStateMachine()->changeState(new PlayState());
	}
};

class ToExit : public EventBase
{
public:
	ToExit() : EventBase()
	{
		s_eventID = "EXIT EVENT";
	}
	virtual void operator()()
	{
		Log::Instance()->write("Info : Exit button clicked!");
		Game::Instance()->setRunning(false);
	}
};
#endif // MENUSTATE_H_