#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_
#include "stdafx.h"
#include "Vector2D.h"

enum MouseButton 
{	LEFT = 1, 
	MIDDLE = 2, 
	RIGHT = 3 };

class InputHandler
{
private:
	InputHandler();
	~InputHandler();

	static InputHandler * s_pInstance;

	bool											m_bJoystickInitialised;
	std::vector<SDL_Joystick*>						m_joysticks;
	std::vector < std::pair<Vector2D*, Vector2D*>>	m_joystickValues;
	std::vector<std::vector<bool>>					m_buttonStates;
	std::vector<bool>								m_mouseButtonStates;
	Vector2D *										m_position;
	const Uint8*									m_keystate;

	const int m_joystickDeadZone = 10000;

	void onKeyDown();
	void onKeyUp();

	void onMouseMove(SDL_Event & event);
	void onMouseButtonDown(SDL_Event & event);
	void onMouseButtonUp(SDL_Event & event);

	void onJoystickAxisMove(SDL_Event & event);
	void onJoystickButtonDown(SDL_Event & event);
	void onJoystickButtonUp(SDL_Event & event);

public:
	void update();
	void clean();
	void release();
	void initialiseJoystick();
	bool isJoystickInitialised();
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);
	bool getButtonState(int joy, int buttonNumber);
	bool getMouseButtonState(int button);
	Vector2D * getMousePosition();
	bool isKeyDown(SDL_Scancode key);

	static InputHandler * Instance();
};

#endif