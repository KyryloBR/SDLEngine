#ifndef SCROLLING_BACKGROUND_H_
#define SCROLLING_BACKGROUND_H_

#include "LoaderParams.h"
#include "stdafx.h"

class ScrollingBackground
{
public:
	void load(const LoaderParams * pParams);
	void draw();
	void update();

private:
	int m_scrollSpeed;
	SDL_Rect srcRect;
	SDL_Rect destRect;
		
};

#endif // SCROLLING_BACKGROUND_H_