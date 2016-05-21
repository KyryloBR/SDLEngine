#ifndef BUTTON_H_
#define BUTTON_H_

#include "EGameObject.h"
#include "GameState.h"
#include "EventBase.h"

enum button_state { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2};

class Button : public EGameObject
{
public:
	Button(EventBase * pEvent);
	Button();

	virtual void load(const LoaderParams * pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void colision() {}
	virtual std::string getType() {return "Button"; }
	int getState() { return m_currentFrame; }

private:
	EventBase * m_pEvent;
	bool m_bReleased;
	int m_currentFrame;
};
#endif // BUTTON_H_