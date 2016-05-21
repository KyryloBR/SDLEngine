#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "stdafx.h"

enum game_sate { MENU = 0, PLAY = 1, GAMEOBER = 2};

class GameState
{
public:
	GameState() {}
	virtual void render() = 0;
	virtual void update() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

protected:
	std::vector<std::string> m_textureIDs;
};

#endif // GAMESTATE_H_