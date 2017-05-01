#include "MathHelpers.h"

bool CheckIntersec(SDL_Rect r1, SDL_Rect r2)
{
	if (r1.x >= r2.x && r1.x <= r2.x + r2.w)
		if (r1.y >= r2.y && r1.y <= r2.y + r2.h)
			return true;

	return false;
}

int RadtoDeg(int rad)
{
	return rad * (180 / M_PI);
}

int DegtoRad(int deg)
{
	return deg * (M_PI / 180);
}
