#ifndef SEQUENCE_STATE_H_
#define SEQUENCE_STATE_H_

#include "GameState.h"
#include "GameStateMachine.h"
#include <map>
#include <stack>

typedef std::pair<int, GameState*> State;

class SequenceState : public GameState
{
public:
	SequenceState();
	~SequenceState();
	void push_state(int durationState, GameState * pState);
	void pop_state();
	void clean();
	void skipState();
	virtual void render();
	virtual	void update();
	virtual bool onEnter();
	virtual bool onExit();

	bool isEmpty() { return m_bEmpty; }

	virtual std::string getStateID() const { return s_seqID; }

private:
	int m_nCurrentTimer;
	int m_nBeginDraw;
	int m_nDurationDraw;
	bool m_bEmpty;
	GameState * m_pCurrentState;
	std::stack<State> m_pStates;
	static const std::string s_seqID;

	void nextState();
};

#endif // SEQUENCE_STATE_H_