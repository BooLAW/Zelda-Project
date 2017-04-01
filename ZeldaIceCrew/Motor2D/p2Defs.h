#ifndef __P2DEFS_H__
#define __P2DEFS_H__

#include <stdio.h>
#include "Point.h"

//  NULL just in case ----------------------

#ifdef NULL
#undef NULL
#endif
#define NULL  0


enum Direction {
	FirstDir = 0,
	Up,
	Left,
	Right,
	Down,
	Up_R,
	Up_L,
	Down_R,
	Down_L,
	LastDir
};

inline fPoint CirclePoints(float cx, float cy, float x, float y, float angle) {
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
};

// Deletes a buffer
#define RELEASE( x ) \
    {                        \
    if( x != NULL )        \
	    {                      \
      delete x;            \
	  x = NULL;              \
	    }                 \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
    {                              \
    if( x != NULL )              \
	    {                            \
      delete[] x;                \
	  x = NULL;                    \
	    }                            \
                              \
    }

#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define TO_BOOL( a )  ( (a != 0) ? true : false )
#define NULLRECT {0,0,0,0}
#define NULLCOLOR {0,0,0,0}
#define NULLPOINT {0,0}
#define COLLIDER_MAX 200

#define PLAYER_COLL_X_OFFSET 8
#define PLAYER_COLL_Y_OFFSET 4

#define ORIGIN_RESTART {300,350}
#define LINK_RECT {0,0,32,32}
typedef unsigned int uint;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
typedef unsigned char uchar;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI       3.1415926535897932384f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !


template <class VALUE_TYPE> void SWAP(VALUE_TYPE& a, VALUE_TYPE& b)
{
	VALUE_TYPE tmp = a;
	a = b;
	b = tmp;
}

// Standard string size
#define SHORT_STR	32
#define MID_STR		255
#define HUGE_STR	8192

// Joins a path and file
inline const char* const PATH(const char* folder, const char* file)
{
	static char path[MID_STR];
	sprintf_s(path, MID_STR, "%s/%s", folder, file);
	return path;
}

// Performance macros
#define PERF_START(timer) timer.Start()
#define PERF_PEEK(timer) LOG("%s took %f ms", __FUNCTION__, timer.ReadMs())

#endif