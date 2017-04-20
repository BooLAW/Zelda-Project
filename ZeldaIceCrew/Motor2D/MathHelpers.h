#ifndef __MATH_HELPERS_H__
#define __MATH_HELPERS_H__

#include "SDL/include/SDL.h"

bool CheckIntersec(SDL_Rect r1, SDL_Rect r2) {

	if (r1.x >= r2.x && r1.x <= r2.x + r2.w)
		if (r1.y >= r2.y && r1.y <= r2.y + r2.h)
			return true;

	return false;
}

#endif !__MATH_HELPERS_H__