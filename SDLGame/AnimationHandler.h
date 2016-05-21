#ifndef _ANIMATION_HANDLER_H
#define _ANIMATION_HANDLER_H_

#include "Animation.h"

class AnimationHandler
{
public:
	void load(const std::string & filename);
	void play(const std::string & _animationID);
	void stop(const std::string & _animationID);
	void pause(const std::string & _animationID);
	void setAlways(const std::string & _animationID, bool _always);
	void setParent(const std::string & _animationID, GameObject * pObject);

	void update();
	void addAnimation(Animation * animation);
	void eraseAnimation(const std::string _animationID);
	void clearAll();

	static AnimationHandler * Instance()
	{
		if (!s_pInstance)
		{
			s_pInstance = new AnimationHandler();
		}
		return s_pInstance;
	}

private:
	std::map<std::string, Animation*> m_animations;
	std::string m_filename;

	static AnimationHandler * s_pInstance;

	AnimationHandler() {}
	~AnimationHandler() { }
	AnimationHandler(const AnimationHandler &) {}
};

#endif // _ANIMATION_HANDLER_H_