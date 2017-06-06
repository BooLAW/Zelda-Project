#include "MathHelpers.h"
#include <math.h>
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

float dot(fPoint a, fPoint b)
{
	return a.x * b.x + a.y * b.y;
}

float mag(fPoint p)
{
	return sqrt(p.x * p.x + p.y * p.y);
}

fPoint CirclePoints(float cx, float cy, float x, float y, float angle)
{
	fPoint point;

	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	x -= cx;
	y -= cy;

	// rotate point
	float xnew = x * c - y * s;
	float ynew = x * s + y * c;

	// translate point back:
	x = xnew + cx;
	y = ynew + cy;

	point = { x, y };

	return point;
}
