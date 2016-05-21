#include "Button.h"
#include "Log.h"
#include "InputHandler.h"
#include "MenuState.h"

Button::Button(EventBase * pEvent) : EGameObject(), m_pEvent(pEvent)
{
	m_currentFrame = MOUSE_OUT;
	m_bReleased = true;
}

Button::Button() : EGameObject()
{
	m_pEvent = nullptr;
	m_bReleased = true;
	m_currentFrame = MOUSE_OUT;
}

void Button::load(const LoaderParams * pParams)
{
	EGameObject::load(pParams);
}


void Button::draw()
{
	EGameObject::draw();
}

void Button::update()
{
	Vector2D * mousePos = InputHandler::Instance()->getMousePosition();
	
	if (mousePos->getX() < (m_position.getX() + m_width)
		&& mousePos->getX() > m_position.getX()
		&& mousePos->getY() < (m_position.getY() + m_height)
		&& mousePos->getY() > m_position.getY())
	{
		if (InputHandler::Instance()->getMouseButtonState(MouseButton::LEFT) && m_bReleased == true)
		{
			m_currentFrame = CLICKED;
			m_bReleased = false;
			(*m_pEvent)();
		}
		else if (!InputHandler::Instance()->getMouseButtonState(MouseButton::LEFT))
		{
			m_currentFrame = MOUSE_OVER;
			m_bReleased = true;
		}
			 
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void Button::clean()
{
	EGameObject::clean();
}