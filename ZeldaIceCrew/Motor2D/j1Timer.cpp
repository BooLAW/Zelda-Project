// ----------------------------------------------------
// j1Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "j1Timer.h"
#include "SDL\include\SDL_timer.h"
#include "Log.h"

// ---------------------------------------------
j1Timer::j1Timer()
{
	Start();
}

// ---------------------------------------------
void j1Timer::Start()
{
	if (flag == false) {
		LOG("HELLO");
		started_at = SDL_GetTicks();
		LOG("HELLO2");
	}
}

void j1Timer::Stop()
{
	flag = false;
}

// ---------------------------------------------
uint32 j1Timer::Read() const
{
	return SDL_GetTicks() - started_at;
}

// ---------------------------------------------
float j1Timer::ReadSec() const
{
	return float(SDL_GetTicks() - started_at) / 1000.0f;
}