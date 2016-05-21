#ifndef COLISION_H_
#define COLISION_H_

#include "stdafx.h"

namespace Colision
{
	const static int s_buffer = 4;

	static bool RectRect(SDL_Rect * first, SDL_Rect * second)
	{
		int fHBuf = first->h / s_buffer;
		int fWBuf = first->w / s_buffer;

		int sHBuf = second->h / s_buffer;
		int sWBuf = second->w / s_buffer;

		if ((first->y + first->h) - fHBuf <= second->y + sHBuf) { return false; }

		if (first->y + fHBuf >= (second->y + second->h) - sHBuf) { return false; }

		if ((first->x + first->w) - fWBuf <= second->x + sWBuf) { return false; }

		if (first->x + fWBuf >= (second->x + second->w) - sWBuf) { return false; }

		return true;
	}
}

#endif // COLISION_H_