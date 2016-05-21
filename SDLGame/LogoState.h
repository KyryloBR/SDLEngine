#ifndef _LOGO_STATE_H_
#define _LOGO_STATE_H_

#include "GameState.h"
#include "EGameObject.h"

class LogoState : public GameState
{
public:
	LogoState(const std::string & logoID, const std::string & filename, int width, int height);
	virtual void render();
	virtual void update();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return "LogoState"; }

private:
	std::string m_logoID;
	int m_height;
	int m_width;
	EGameObject * m_logo;
};

#endif // _LOGO_STATE_H_