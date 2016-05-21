#ifndef _SHEET_ANIMATION_H_
#define _SHEET_ANIMATION_H_

#include "Animation.h"

class SheetAnimation : public Animation
{
public:
	SheetAnimation(const std::string & _animationID, int nNumFrames) : Animation(_animationID),m_nNumFrames(nNumFrames),
		m_bAlways(true), m_bReverse(false), m_nCurrentRow(1), m_nCurrentFrame(0)
	{

	}

	virtual void update();

	void setNumLoop(int _loop);
	void setReverse(bool _reverse);
	void setAlways(bool _always);

	int getCurrentFrame() { return m_nCurrentFrame; }
	int getCurrentRow() { return m_nCurrentRow; }
	int getNumFrames() { return m_nNumFrames; }

private:
	int m_nCurrentRow;
	int m_nCurrentFrame;
	int m_nNumFrames;
	int m_nLoop;
	
	bool m_bReverse;
	bool m_bAlways;
};

#endif // _SHEET_ANIMATION_H_