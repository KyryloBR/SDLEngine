#include "InputHandler.h"
#include "Log.h"
#include "Game.h"

InputHandler * InputHandler::s_pInstance = 0;

InputHandler::InputHandler()
{
	m_position = new Vector2D();
	for (int i = 0; i < 3; ++i)
		m_mouseButtonStates.push_back(false);
}
InputHandler::~InputHandler()
{
}

void InputHandler::onKeyDown()
{
	m_keystate = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	m_keystate = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseButtonDown(SDL_Event & event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			m_mouseButtonStates[LEFT - 1] = true;
			Log::Instance()->write("Info : Mouse button left down." + std::string(std::to_string(getMousePosition()->getX())) + std::string(std::to_string(getMousePosition()->getY())));
		}
		if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			m_mouseButtonStates[MIDDLE - 1] = true;
			Log::Instance()->write("Info : Mouse button middle down.");
		}
		if (event.button.button == SDL_BUTTON_RIGHT)
		{
			m_mouseButtonStates[RIGHT - 1] = true;
			Log::Instance()->write("Info : Mouse button right down.");
		}
	}
}
void InputHandler::onMouseButtonUp(SDL_Event & event)
{
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			m_mouseButtonStates[LEFT - 1] = false;
			Log::Instance()->write("Info : Mouse button left up.");
		}
		if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			m_mouseButtonStates[MIDDLE - 1] = false;
			Log::Instance()->write("Info : Mouse button middle up.");
		}
		if (event.button.button == SDL_BUTTON_RIGHT)
		{
			m_mouseButtonStates[RIGHT - 1] = false;
			Log::Instance()->write("Info : Mouse button right up.");
		}
	}
}

void InputHandler::onMouseMove(SDL_Event & event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		m_position->setX(event.motion.x);
		m_position->setY(event.motion.y);
	}
}

void InputHandler::onJoystickAxisMove(SDL_Event & event)
{
	if (event.type == SDL_JOYAXISMOTION)
	{
		int whichOne = event.jaxis.which;
		if (event.jaxis.which == 0)
		{
			if (event.jaxis.value > m_joystickDeadZone)
			{
				m_joystickValues[whichOne].first->setX(1);
			}
			else if (event.jaxis.value < -m_joystickDeadZone)
			{
				m_joystickValues[whichOne].first->setX(-1);
			}
			else
			{
				m_joystickValues[whichOne].first->setX(0);
			}
		}
		if (event.jaxis.which == 1)
		{
			if (event.jaxis.value > m_joystickDeadZone)
			{
				m_joystickValues[whichOne].first->setY(1);
			}
			else if (event.jaxis.value < -m_joystickDeadZone)
			{
				m_joystickValues[whichOne].first->setY(-1);
			}
			else
			{
				m_joystickValues[whichOne].first->setY(0);
			}
		}
		if (event.jaxis.which == 3)
		{
			if (event.jaxis.value > m_joystickDeadZone)
			{
				m_joystickValues[whichOne].second->setX(1);
			}
			else if (event.jaxis.value < -m_joystickDeadZone)
			{
				m_joystickValues[whichOne].second->setX(-1);
			}
			else
			{
				m_joystickValues[whichOne].second->setX(0);
			}
		}
		if (event.jaxis.which == 4)
		{
			if (event.jaxis.value > m_joystickDeadZone)
			{
				m_joystickValues[whichOne].second->setY(1);
			}
			else if (event.jaxis.value < -m_joystickDeadZone)
			{
				m_joystickValues[whichOne].second->setY(-1);
			}
			else
			{
				m_joystickValues[whichOne].second->setY(0);
			}
		}
	}
}

void InputHandler::onJoystickButtonDown(SDL_Event & event)
{
	if (event.type == SDL_JOYBUTTONDOWN)
	{
		int whichOne = event.jaxis.which;
		m_buttonStates[whichOne][event.jbutton.button] = true;
		Log::Instance()->write("Info : Joystick button down.");
	}
}

void InputHandler::onJoystickButtonUp(SDL_Event & event)
{
	if (event.type == SDL_JOYBUTTONUP)
	{
		int whichOne = event.jaxis.which;
		m_buttonStates[whichOne][event.jbutton.button] = false;
		Log::Instance()->write("Info : Joystick button up.");
	}
}

InputHandler * InputHandler::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new InputHandler();
	}
	return s_pInstance;
}
void InputHandler::release()
{
	if (!s_pInstance)
	{
		delete s_pInstance;
	}
}

void InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Game::Instance()->setRunning(false);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_JOYAXISMOTION:
			onJoystickAxisMove(event);
			break;

		case SDL_JOYBUTTONDOWN:
			onJoystickButtonDown(event);
			break;

		case SDL_JOYBUTTONUP:
			onJoystickButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;
		default:
			break;
		}
	}
}

void InputHandler::clean()
{
	if (m_bJoystickInitialised)
	{
		for (int i = 0; i < m_joysticks.size(); ++i)
		{
			SDL_JoystickClose(m_joysticks.at(i));
		}
	}
}

void InputHandler::initialiseJoystick()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		Log::Instance()->write("Joystick was initialised.");
	}
	else
	{
		Log::Instance()->write("Info : Joystick wasn`t initialised.");
	}
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); ++i)
		{
			SDL_Joystick * joy = SDL_JoystickOpen(i);
			if (joy)
			{
				m_joysticks.push_back(joy);
				m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));
				std::vector<bool> tempButtons;
				for (int i = 0; i < SDL_JoystickNumButtons(joy); ++i)
				{
					tempButtons.push_back(false);
				}
				m_buttonStates.push_back(tempButtons);
			}
			else
			{
				Log::Instance()->write(SDL_GetError());
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoystickInitialised = true;
		Log::Instance()->write("Initialised joysticks");
	}
	else
	{
		m_bJoystickInitialised = false;
	}
}

int InputHandler::xvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getX();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getX();
		}
	}
	return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getY();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getY();
		}
	}
	return 0;
}
bool InputHandler::isJoystickInitialised()
{
	return m_bJoystickInitialised;
}

bool InputHandler::getButtonState(int joy, int buttonNumber)
{
	return m_buttonStates[joy][buttonNumber];
}

bool InputHandler::getMouseButtonState(int button)
{
	if (m_mouseButtonStates[button - 1])
	{
		Log::Instance()->write("LEFT BUTTON DOWN");
	}
	return m_mouseButtonStates[button - 1];
}
Vector2D * InputHandler::getMousePosition()
{
	return m_position;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystate != 0)
	{
		if (m_keystate[key] == 1)
		{
			return true;
		}
	}
	return false;
}