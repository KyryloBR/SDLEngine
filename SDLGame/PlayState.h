#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "GameState.h"
#include "GameObject.h"
#include "Level.h"
#include "LoopAnimation.h"

class PlayState : public GameState
{
private:
		static const std::string s_playID;
		std::vector<GameObject*> m_gameObjects;

		Tileset m_Player;
		Level * m_pLevel;

public:
	PlayState() {}
	virtual void render();
	virtual void update();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }
};

#endif // PLAYSTATE_H_