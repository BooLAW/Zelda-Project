#ifndef __MATH_HELPERS_H__
#define __MATH_HELPERS_H__

#include "SDL/include/SDL.h"
#include "Point.h"

bool CheckIntersec(SDL_Rect r1, SDL_Rect r2);

int RadtoDeg(int rad);
int DegtoRad(int deg);

float dot(fPoint a, fPoint b);
float mag(fPoint p);

fPoint CirclePoints(float cx, float cy, float x, float y, float angle);

#endif !__MATH_HELPERS_H__