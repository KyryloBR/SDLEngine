#ifndef GAMESTATEMACHINE_H_
#define GAMESTATEMACHINE_H_

#include "EGameObject.h"
#include "GameState.h"

class GameStateMachine
{
private:
	std::vector<GameState*> m_states;
public:
	GameStateMachine() {};
	void push_back(GameState* pState);
	void pop_state();
	void changeState(GameState* pState);

	void update();
	void render();
};

#endif // GAMESTATEMACHINE_H_