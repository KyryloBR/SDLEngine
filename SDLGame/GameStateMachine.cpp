#include "GameStateMachine.h"
#include "Log.h"
#include "SequenceState.h"

void GameStateMachine::push_back(GameState * pState)
{
	m_states.push_back(pState);
	m_states.back()->onEnter();
}

void GameStateMachine::changeState(GameState * pState)
{
	if (!m_states.empty())
	{
		if (m_states.back()->getStateID() == pState->getStateID())
		{
			Log::Instance()->write("Warning : state already load.");
			return;
		}
		if (m_states.back()->onExit())
		{
			m_states.pop_back();
		}
		m_states.push_back(pState);
		m_states.back()->onEnter();
	}
}

void GameStateMachine::pop_state()
{
	if (!m_states.empty())
	{
		if (m_states.back()->onExit())
		{
			delete m_states.back();
			m_states.pop_back();
		}
	}
}

void GameStateMachine::update()
{
	if (!m_states.empty())
	{
		if (m_states.back()->getStateID() == std::string("Sequence"))
		{
			if (dynamic_cast<SequenceState*>(m_states.back())->isEmpty())
			{
				pop_state();
			}
		}
		m_states.back()->update();
	}
}

void GameStateMachine::render()
{
	if (!m_states.empty())
	{
		m_states.back()->render();
	}
}