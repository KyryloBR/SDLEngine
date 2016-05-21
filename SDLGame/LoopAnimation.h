#ifndef LOOP_ANIMATION_H_
#define LOOP_ANIMATION_H_

#include "Animation.h"

class LoopAnimation : public Animation
{
public:
	LoopAnimation(const std::string & animationID) : Animation(animationID), m_currentIndex(0) {}
	void addFrame(int id, const std::string & frame);
	virtual void update();

	// Methods for set params animation.
	void setLoop(int loop);
	void setIndexBegin(int index);
	void setLoopAlways(bool loop);

	// Methods for get params animation.
	int getLoop() { return m_loop; }
	int getCountFrames() { return m_frames.size(); }
	int getCurrentIndex() { return m_currentIndex; }
	bool isAlways() { return m_bLoop; }
	std::string getCurrentId();

private:
	std::map<std::string,std::string> m_frames;
	int m_currentIndex;
	int m_loop;
	bool m_bLoop;
};

#endif // LOOP_ANIMATION_H_