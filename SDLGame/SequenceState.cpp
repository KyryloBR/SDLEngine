#include "SequenceState.h"
#include "stdafx.h"
#include "Game.h"

const std::string SequenceState::s_seqID = "Sequence";

SequenceState::SequenceState() : GameState()
{
}

SequenceState::~SequenceState()
{
}

void SequenceState::push_state(int durationState, GameState * pState)
{
	if (pState)
	{
		m_pStates.push(std::make_pair(durationState, pState));
	}
}

void SequenceState::pop_state()
{
	m_pStates.pop();
}

bool SequenceState::onEnter()
{
	if (m_pStates.empty())
	{
		return false;
	}
	m_pCurrentState = m_pStates.top().second;
	m_nDurationDraw = m_pStates.top().first;
	m_nBeginDraw = SDL_GetTicks();
	m_pCurrentState->onEnter();
	return true;
}

bool SequenceState::onExit()
{
	if (m_pCurrentState->onExit())
	{
		return true;
	}
	return false;
}

void SequenceState::render()
{
	if (!m_pCurrentState || m_bEmpty)
	{
		return;
	}
	m_pCurrentState->render();
}

void SequenceState::skipState()
{
	nextState();
}

void SequenceState::update()
{
	if (!m_bEmpty)
	{
		int nDurationTime = SDL_GetTicks() - m_nBeginDraw;
		if (nDurationTime >= m_nDurationDraw)
		{
			if (m_pStates.size() == 1)
			{
				m_bEmpty = true;
				onExit();
				m_pStates.pop();
				return;
			}
			nextState();
		}
		if (!m_pCurrentState)
		{
			return;
		}
		m_pCurrentState->update();
	}
}

void SequenceState::clean()
{
	m_pCurrentState->onExit();
}

void SequenceState::nextState()
{
	if (!m_pCurrentState)
	{
		return;
	}
	m_pCurrentState->onExit();
	m_pStates.pop();
	m_pCurrentState = m_pStates.top().second;
	m_nDurationDraw = m_pStates.top().first;
	m_nBeginDraw = SDL_GetTicks();
	m_pCurrentState->onEnter();
}